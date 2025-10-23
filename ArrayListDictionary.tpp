template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::numComps = 0;

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(int i)
: list(new ArrayList<Record>(i)) { }

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(const ArrayListDictionary<Key, Val>& copyObj) {
    copy(copyObj);
}

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>& ArrayListDictionary<Key, Val>::operator=(const ArrayListDictionary<Key, Val>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::~ArrayListDictionary() {
    delete list;
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchIter(const Key& target, int left, int right) const {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Key midKey = list->getElement(mid).k;

        numComps++; // For the == comparison
        if (target == midKey) {
            return list->getElement(mid).v; // Found it
        }

        numComps++; // For the < comparison
        if (target < midKey) {
            right = mid - 1; // Search the left half
        } else {
            left = mid + 1;  // Search the right half
        }
    }
    
    // The loop finished (left > right), so the key was not found.
    throw -1;
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchRec(const Key& target, int left, int right) const {
    // Base Case 1: The search space is empty.
    if (left > right) {
        throw -1; // Key not found
    }

    int mid = left + (right - left) / 2;
    Key midKey = list->getElement(mid).k;

    numComps++; // For the == comparison
    // Base Case 2: Found it.
    if (target == midKey) {
        return list->getElement(mid).v;
    }

    numComps++; // For the < comparison
    // Recursive Step: Search the correct half.
    if (target < midKey) {
        return binSearchRec(target, left, mid - 1); // Search left
    } else {
        return binSearchRec(target, mid + 1, right); // Search right
    }
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::clear() {
    list->clear();
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::copy(const ArrayListDictionary<Key, Val>& copyObj) {
    list = new ArrayList<Record>(*copyObj.list);
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::find(const Key& k) const {
    numComps = 0;

    try {
        return seqSearchIter(k);
        // return seqSearchRec(k);
        // return binSearchIter(k, 0, list->getLength() - 1);
        // return binSearchRec(k, 0, list->getLength() - 1);
    }
    catch (...) {
        throw string("find: error, unsuccessful search, target key not found");
    }
}

template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::getNumComps() {
    return numComps;
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::insert(const Key& k, const Val& v) {
    list->append(Record(k, v));
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::remove(const Key& k) {
    bool flag = false;

    for (int i = 0; i < list->getLength(); i++) {
        if (list->getElement(i).k == k) {
            list->remove(i);
            flag = true;
            break;
        }
    }

    if (!flag) {
        throw string("remove: error, unable to find record with matching key to remove");
    }
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchIter(const Key& target) const {
    for (int i = 0; i < list->getLength(); i++) {
        // Increment for each key comparison
        numComps++;
        if (list->getElement(i).k == target) {
            return list->getElement(i).v; // Found it
        }
    }
    
    // Looped through the whole list and didn't find it
    throw -1; 
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchRec(const Key& target, int i) const {
    // Base Case 1: We've gone past the end of the list.
    if (i >= list->getLength()) {
        throw -1; // Key not found
    }

    // Increment for this element's key comparison
    numComps++;
    
    // Base Case 2: We found the key.
    if (list->getElement(i).k == target) {
        return list->getElement(i).v;
    }

    // Recursive Step: Check the next element in the list.
    return seqSearchRec(target, i + 1);
}

template <typename Key, typename Val>
int ArrayListDictionary<Key, Val>::size() const {
    return list->getLength();
}

