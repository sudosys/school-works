typedef int KeyType;

class KeyedItem {
   public:
      KeyedItem() {};
      KeyedItem(const KeyType& keyValue) : searchKey(keyValue) {}
      KeyType getKey() const { return searchKey; }
   private:
      KeyType searchKey;
};
