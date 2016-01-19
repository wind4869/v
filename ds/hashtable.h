#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <algorithm>
using namespace std;

template <typename Value>
struct hashtable_node {
    hashtable_node* next;
    Value val;
};

static const int num_primes = 28;
static const unsigned long prime_list[num_primes] = {
  53,         97,           193,         389,       769,
  1543,       3079,         6151,        12289,     24593,
  49157,      98317,        196613,      393241,    786433,
  1572869,    3145739,      6291469,     12582917,  25165843,
  50331653,   100663319,    201326611,   402653189, 805306457, 
  1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long next_prime(unsigned long n)
{
    const unsigned long* first = prime_list;
    const unsigned long* last = prime_list + num_primes;
    const unsigned long* pos = lower_bound(first, last, n);
    return pos == last ? *(last - 1) : *pos;
}

template <typename Value, typename Key, typename HashFcn,
          typename ExtractKey, typename EqualKey>
class hashtable {
public:
    typedef Value value_type;
    typedef Key key_type;
    typedef HashFcn hasher;
    typedef EqualKey key_equal;
    typedef size_t size_type;
private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;
    
    typedef hashtable_node<Value> node;

    vector<node*> buckets;
    size_type num_elements;
public:
    hashtable() : 
        hash(hasher()), 
        equals(key_equal()), 
        get_key(ExtractKey()),
        num_elements(0)
    {
        initialize_buckets(0);
    }

    ~hashtable() { clear(); }

    size_type size() { return num_elements; }

    size_type bucket_count() const { return buckets.size(); }

    size_type max_bucket_count() const { return prime_list[num_primes - 1]; }

    size_type elems_in_bucket(size_type bucket) const
    {
        size_type result = 0;
        for (node* cur = buckets[bucket]; cur; cur = cur->next)
            result += 1;
        return result;
    }

    value_type find(const key_type& key)
    {
        size_type n = bkt_num_key(key);
        node* first;

        for (first = buckets[n];
             first && !equals(get_key(first->val), key);
             first = first->next) {  } 

        if (first)
            return first->val;
        else
            return value_type();
    }

    size_type count(const key_type& key) const 
    {
        const size_type n = bkt_num_key(key);
        size_type result = 0;
        for (const node* cur = buckets[n]; cur; cur = cur->next)
            if (equals(get_key(cur->val), key))
                ++result;
        return result;
    }

    bool insert_unique(const value_type& obj)
    {
        resize(num_elements + 1);
        return insert_unique_noresize(obj);
    }

    void insert_equal(const value_type& obj)
    {
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    void resize(size_type num_elements_hint)
    {
        const size_type old_n = buckets.size();
        if (num_elements_hint > old_n) {
            const size_type n = next_size(num_elements_hint);
            if (n > old_n) {
                vector<node*> tmp(n, (node*)0);
                for (size_type bucket = 0; bucket < old_n; ++bucket) {
                    node* first = buckets[bucket];
                    while (first) {
                        size_type new_bucket = bkt_num(first->val, n);
                        buckets[bucket] = first->next;
                        first->next = tmp[new_bucket];
                        tmp[new_bucket] = first;
                        first = buckets[bucket];
                    }
                }
                buckets.swap(tmp);
            }
        }
    }

    bool insert_unique_noresize(const value_type& obj)
    {
        const size_type n = bkt_num(obj);
        node* first = buckets[n];

        for (node* cur = first; cur; cur = cur->next)
            if (equals(get_key(cur->val), get_key(obj)))
                return false;

        node* tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return true;
    }

    void insert_equal_noresize(const value_type& obj)
    {
        const size_type n = bkt_num(obj);
        node* first = buckets[n];

        for (node* cur = first; cur; cur = cur->next)
            if (equals(get_key(cur->val), get_key(obj))) {
                node* tmp = new_node(obj);
                tmp->next = cur->next;
                cur->next = tmp;
                ++num_elements;
                return;
            }

        node* tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
    }

    void clear()
    {
        for (size_type i = 0; i < buckets.size(); ++i) {
            node* cur = buckets[i];

            while (cur != 0) {
                node* next = cur->next;
                delete_node(cur);
                cur = next;
            }
            buckets[i] = 0;
        }
        num_elements = 0;
    }

    void copy_from(const hashtable& ht)
    {
        buckets.clear();
        buckets.reserve(ht.buckets.size());
        buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);

        for (size_type i = 0; i < ht.buckets.size(); ++i) {
            if (const node* cur = ht.buckets[i]) {
                node* copy = new_node(cur->val);
                buckets[i] = copy;

                for (node* next = cur->next; next; cur = next, next = cur->next) {
                    copy->next = new_node(next->val);
                    copy = copy->next;
                }
            }
        }
        num_elements = ht.num_elements;
    }

private:
    size_type next_size(size_type n) const { return next_prime(n); }

    void initialize_buckets(size_type n)
    {
        const size_type n_buckets = next_size(n);
        buckets.reserve(n_buckets);
        buckets.insert(buckets.end(), n_buckets, (node*)0);
        num_elements = 0;
    }

    size_type bkt_num_key(const key_type& key) const
    {
        return bkt_num_key(key, buckets.size());
    }

    size_type bkt_num(const value_type& obj) const
    {
        return bkt_num_key(get_key(obj));
    }

    size_type bkt_num_key(const key_type& key, size_type n) const
    {
        return hash(key) % n;
    }

    size_type bkt_num(const value_type& obj, size_type n) const
    {
        return bkt_num_key(get_key(obj), n);
    }

    node* new_node(const value_type& obj)
    {
        node* p = new node();
        p->next = 0;
        p->val = obj;
        return p;
    }

    void delete_node(node* p) { delete p; }
};

#endif
