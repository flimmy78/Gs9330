#ifndef _SectionBase_h_
#define _SectionBase_h_

#include "Types.h"
/**********************class Component**********************/
class Component
{
public:
    Component() {}
    virtual ~Component() {}

    virtual size_t GetCodesSize() const = 0;
    virtual size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const = 0;

    /* the following function is provided just for debug */
    int Compare(const Component& right) const;
    virtual void Put(std::ostream& os) const = 0;
};

inline bool operator==(const Component& left, const Component& right)
{ 
    return (left.Compare(right) == 0); 
} 
inline bool operator!=(const Component& left, const Component& right) 
{ 
    return (left.Compare(right) != 0); 
} 
inline bool operator>(const Component& left, const Component& right) 
{ 
    return (left.Compare(right) > 0); 
} 
inline bool operator<(const Component& left, const Component& right) 
{ 
    return (left.Compare(right) < 0); 
} 
inline std::ostream& operator << (std::ostream& os, const Component& value) 
{ 
    value.Put(os); 
    return os; 
}

/**********************class Components**********************/
// 4 bits reserved_future_use + 12 bits transport_stream_loop_length + list of Component. 
class Components: public Component
{
public:
    Components(){}
    virtual ~Components() {}

    void AddComponent(const std::shared_ptr<Component>& component);
    size_t GetCodesSize() const;
    virtual size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const;
    virtual size_t MakeCodes(uchar_t *buffer, size_t bufferSize, uchar_t reserved4Bit) const;

    /* the following function is provided just for debug */
    virtual void Put(std::ostream& os) const;

protected:
    std::list<std::shared_ptr<Component>> components;
};

/**********************class Descriptor**********************/
class Descriptor: public Component
{
public:    
    Descriptor() {}
    virtual ~Descriptor() {}

    virtual uchar_t GetTag() const = 0;
    virtual size_t GetCodesSize() const = 0;
    virtual size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const = 0;

    /* the following function is provided just for debug */
    virtual void Put(std::ostream& os) const = 0;
};

/**********************class Section**********************/
class Section: public Component
{
public:
    Section(const char *key): key(key) {}
    virtual ~Section() {}
    
    virtual std::string GetKey() { return key; }
    /* for BAT return bouquet_id, for Eit return service_id, 
       for Nit return network_id, for Sdt return transport_stream_id
    */
    virtual uint16_t GetSectionId() const = 0;
    virtual uint16_t GetNetworkId() const = 0;
    virtual uint16_t GetPid()  const = 0; 
    virtual uchar_t GetTableId() const = 0;
    
    virtual size_t GetCodesSize() const = 0;
    virtual size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const = 0;

    /* the following function is provided just for debug */
    virtual void Put(std::ostream& os) const = 0;

protected:
    /* we regard a section as a iterm in table, tableKey is the key for current record
    */
    std::string key;
};

class CompareSectionNetId : public std::unary_function<Section, bool>
{
public:
    CompareSectionNetId(uint16_t netId): netId(netId)
    {}

    bool operator()(const std::shared_ptr<argument_type>& arg) const
    {
        if (arg->GetNetworkId() == netId)
            return true;

        return false;
    }

private:
    uint16_t netId;
};

class CompareSectionKey: public std::unary_function<Section, bool>
{
public:
    CompareSectionKey(const char *key): key(key)
    {}

    bool operator()(const std::shared_ptr<argument_type>& arg) const
    {
        if (arg->GetKey() == key)
            return true;

        return false;
    }

private:
    std::string key;
};


#endif