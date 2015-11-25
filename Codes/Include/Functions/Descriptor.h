#ifndef _Descriptor_h_
#define _Descriptor_h_

#include "Component.h"
/**********************class UcharDescriptor**********************/
class UcharDescriptor: public Descriptor
{
public: 
    UcharDescriptor(uchar_t *theData, size_t theDataSize) 
        : data(new uchar_t[theDataSize+1], UcharDeleter()), dataSize(theDataSize)
    { 
        /* we allocate 1 more bytes to store '0', just for debug function Put() to
        show the value correctly.
        */
        data.get()[theDataSize] = '\0';
        memcpy(data.get(), theData, theDataSize);
    }

    virtual ~UcharDescriptor()
    {}

    virtual uchar_t GetTag() const = 0;
    size_t GetCodesSize() const;
    size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const;

    /* the following function is provided just for debug */
    void Put(std::ostream& os) const;

protected:
    std::shared_ptr<uchar_t> data;
    size_t dataSize;
};

class DescriptorCreator
{
public:
    DescriptorCreator() {}
    virtual ~DescriptorCreator() {}

    /* Create descriptor from string. */
    virtual Descriptor* CreateInstance(uchar_t *data) { return nullptr; }

    /* Create descriptor from binary (for example .ts file). */
    virtual Descriptor* CreateInstance(uchar_t *data, size_t dataSize) { return nullptr; }
};

/**********************class NetworkNameDescriptor**********************/
/* network_name_descriptor */
class NetworkNameDescriptor: public UcharDescriptor
{
public:
    enum: uchar_t {Tag  = 0x40};

    NetworkNameDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}
    uchar_t GetTag() const { return Tag; }
};

class NetworkNameDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        std::string networkName;
        data =  data + ConvertUtf8ToString(data, networkName);

        return new NetworkNameDescriptor((uchar_t*)networkName.c_str(), networkName.size());
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new NetworkNameDescriptor(data, dataSize); 
    }
};

/**********************class ServiceListDescriptor**********************/
/* service_list_descriptor */
class ServiceListDescriptor: public UcharDescriptor
{
public: 
    enum: uchar_t {Tag  = 0x41};

    ServiceListDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}
    uchar_t GetTag() const { return Tag; }
};

class ServiceListDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        assert(descriptorLenght % 3 == 0);
        std::shared_ptr<uchar_t> buffer(new uchar_t[descriptorLenght], UcharDeleter());
        uchar_t *ptr = buffer.get();

        for (size_t i = 0; i < descriptorLenght; i = i + 3)
        {
            uint16_t serviceId;
            uchar_t  serviceType;

            data = data + ConvertHexStrToInt(data, serviceId);
            data = data + ConvertHexStrToInt(data, serviceType);

            ptr = ptr + WriteBuffer(ptr, serviceId);
            ptr = ptr + WriteBuffer(ptr, serviceType);
        }

        return new ServiceListDescriptor(buffer.get(), descriptorLenght);
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new ServiceListDescriptor(data, dataSize); 
    }
};

/**********************class StuffingDescriptor**********************/
/* stuffing_descriptor */
class StuffingDescriptor: public UcharDescriptor
{
public: 
    enum: uchar_t {Tag  = 0x42};
    StuffingDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class StuffingDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        /* ToDo: Convert Utf8 to Gb2312 */
        return new ServiceListDescriptor(data, descriptorLenght);
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new StuffingDescriptor(data, dataSize); 
    }
};

/**********************class SatelliteDeliverySystemDescriptor**********************/
/* satellite_delivery_system_descriptor */
class SatelliteDeliverySystemDescriptor: public UcharDescriptor
{
public: 
    enum: uchar_t {Tag  = 0x43};
    SatelliteDeliverySystemDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class SatelliteDeliverySystemDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        std::shared_ptr<uchar_t> buffer(new uchar_t[descriptorLenght], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uint32_t frequency;
        uint16_t orbitalPosition;
        uchar_t  weastEastFlag; //west_east_flag + polarization + roll off/"00" + modulation_system + modulation_type
        uint32_t symbolRate;    //symbol_rate + FEC_inner

        data = data + ConvertHexStrToInt(data, frequency);
        data = data + ConvertHexStrToInt(data, orbitalPosition);
        data = data + ConvertHexStrToInt(data, weastEastFlag);
        data = data + ConvertHexStrToInt(data, symbolRate);

        ptr = ptr + WriteBuffer(ptr, frequency);
        ptr = ptr + WriteBuffer(ptr, orbitalPosition);
        ptr = ptr + WriteBuffer(ptr, weastEastFlag);
        ptr = ptr + WriteBuffer(ptr, symbolRate);

        return new SatelliteDeliverySystemDescriptor(buffer.get(), descriptorLenght);
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new SatelliteDeliverySystemDescriptor(data, dataSize); 
    }
};

/**********************class CableDeliverySystemDescriptor**********************/
/* cable_delivery_system_descriptor  */
class CableDeliverySystemDescriptor: public UcharDescriptor
{
public: 
    enum: uchar_t {Tag  = 0x44};
    CableDeliverySystemDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class CableDeliverySystemDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        std::shared_ptr<uchar_t> buffer(new uchar_t[descriptorLenght], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uint32_t frequency;
        uint16_t reserved; //reserved_future_use + FEC_outer
        uchar_t  modulation; 
        uint32_t symbolRate;   

        data = data + ConvertHexStrToInt(data, frequency);
        data = data + ConvertHexStrToInt(data, reserved);
        data = data + ConvertHexStrToInt(data, modulation);
        data = data + ConvertHexStrToInt(data, symbolRate);

        ptr = ptr + WriteBuffer(ptr, frequency);
        ptr = ptr + WriteBuffer(ptr, reserved);
        ptr = ptr + WriteBuffer(ptr, modulation);
        ptr = ptr + WriteBuffer(ptr, symbolRate);

        return new CableDeliverySystemDescriptor(buffer.get(), descriptorLenght);
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new CableDeliverySystemDescriptor(data, dataSize); 
    }
};

/**********************class NetworkNameDescriptor**********************/
/* bouquet_name_descriptor */
class BouquetNameDescriptor: public UcharDescriptor
{
public:
    enum: uchar_t {Tag  = 0x47};
    BouquetNameDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class BouquetNameDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {        
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        std::string bouquetName;
        data =  data + ConvertUtf8ToString(data, bouquetName);

        return new BouquetNameDescriptor((uchar_t*)bouquetName.c_str(), bouquetName.size());
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new BouquetNameDescriptor(data, dataSize); 
    }
};

/**********************class ServiceDescriptor**********************/
/* service_descriptor  */
class ServiceDescriptor: public UcharDescriptor
{
public: 
    enum: uchar_t {Tag  = 0x48};
    ServiceDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class ServiceDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        size_t dataSize = 3 + (descriptorLenght - 3) * 2 + 2 /* 0x13, language ID */;
        std::shared_ptr<uchar_t> buffer(new uchar_t[dataSize], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uchar_t serviceType, serviceProviderNameLength, serviceNameLength;
        std::string serviceProviderName, serviceName;

        data = data + ConvertHexStrToInt(data, serviceType);
        data = data + ConvertHexStrToInt(data, serviceProviderNameLength);
        data = data + ConvertUtf8ToString(data, serviceProviderName, serviceProviderNameLength);
        data = data + ConvertHexStrToInt(data, serviceNameLength);
        data = data + ConvertUtf8ToString(data, serviceName, serviceNameLength);        

        ptr = ptr + WriteBuffer(ptr, serviceType);
        ptr = ptr + WriteBuffer(ptr, (uchar_t)serviceProviderName.size());
        ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), serviceProviderName.c_str(), serviceProviderName.size());
        ptr = ptr + WriteBuffer(ptr, (uchar_t)serviceName.size());
        ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), serviceName.c_str(), serviceName.size());

        return new ServiceDescriptor(buffer.get(), ptr - buffer.get());  
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new ServiceDescriptor(data, dataSize); 
    }
};

/**********************class ShortEventDescriptor**********************/
/* short_event_descriptor */
class ShortEventDescriptor: public UcharDescriptor
{
public:
    enum: uchar_t {Tag  = 0x4D};
    ShortEventDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class ShortEventDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {   
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        size_t dataSize = 5 + (descriptorLenght - 5) * 2 + 2 /* 0x13, language ID */;
        std::shared_ptr<uchar_t> buffer(new uchar_t[dataSize], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uchar_t languageCode[3];
        uchar_t eventNameLength;
        std::string eventName;
        uchar_t textLength;
        std::string text;
        data = data + MemCopy(languageCode, 3, data, 3);
        data = data + ConvertHexStrToInt(data, eventNameLength);
        data = data + ConvertUtf8ToString(data, eventName, eventNameLength);
        data = data + ConvertHexStrToInt(data, textLength);
        data = data + ConvertUtf8ToString(data, text, textLength);     

        ptr = ptr + MemCopy(ptr, 3, languageCode, 3);
        ptr = ptr + WriteBuffer(ptr, (uchar_t)eventName.size());
        ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), eventName.c_str(), eventName.size());
        ptr = ptr + WriteBuffer(ptr, (uchar_t)text.size());
        ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), text.c_str(), text.size());

        return new ShortEventDescriptor(buffer.get(), ptr - buffer.get());
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new ShortEventDescriptor(data, dataSize); 
    }
};

/**********************class ExtendedEventDescriptor**********************/
/* extended_event_descriptor */
class ExtendedEventDescriptor: public UcharDescriptor
{
public:
    enum: uchar_t {Tag  = 0x4E};
    ExtendedEventDescriptor(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    uchar_t GetTag() const { return Tag; }
};

class ExtendedEventDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        size_t dataSize = 0xff;
        std::shared_ptr<uchar_t> buffer(new uchar_t[dataSize], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uchar_t descriptorNumber;  //descriptor_number + last_descriptor_number
        uchar_t languageCode[3];
        uchar_t lengthOfItem;      //for now,  the length_of_items should always be 0.
        uchar_t textLength;        
        std::string text;

        data = data + ConvertHexStrToInt(data, descriptorNumber);
        ptr = ptr + WriteBuffer(ptr, descriptorNumber);

        data = data + MemCopy(languageCode, 3, data, 3);
        ptr = ptr + MemCopy(ptr, 3, languageCode, 3);

        data = data + ConvertHexStrToInt(data, lengthOfItem);
        uchar_t *ptrToLengthOfItem = ptr;
        ptr = ptr + WriteBuffer(ptr, 0);
        while (lengthOfItem > 0)
        {
            uchar_t itemDescriptionLength, itemLength;
            std::string itemDescriptionChar, itemChar;

            data = data + ConvertHexStrToInt(data, itemDescriptionLength);
            data = data + ConvertUtf8ToString(data, itemDescriptionChar, itemDescriptionLength);
            ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), 
                itemDescriptionChar.c_str(), itemDescriptionChar.size());

            data = data + ConvertHexStrToInt(data, itemLength);
            data = data + ConvertUtf8ToString(data, itemChar, itemLength);
            ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), 
                itemChar.c_str(), itemChar.size());

            assert(lengthOfItem >= itemDescriptionChar.size() + itemChar.size());
            lengthOfItem = lengthOfItem - (itemDescriptionChar.size() + itemChar.size());
        }
        
        data = data + ConvertHexStrToInt(data, textLength);
        data = data + ConvertUtf8ToString(data, text, textLength);

        
        ptr = ptr + WriteBuffer(ptr, lengthOfItem);
        ptr = ptr + WriteBuffer(ptr, (uchar_t)text.size());
        ptr = ptr + MemCopy(ptr, dataSize - (ptr - buffer.get()), text.c_str(), text.size());

        return new ExtendedEventDescriptor(buffer.get(), ptr - buffer.get());
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new ExtendedEventDescriptor(data, dataSize); 
    }
};

/**********************class UserdefinedDscriptor83**********************/
/* user defined dscriptor, LCN 和音量补偿  */
class UserdefinedDscriptor83: public UcharDescriptor
{
public: 
    enum: uchar_t {Tag  = 0x83};
    UserdefinedDscriptor83(uchar_t *data, size_t dataSize)
        : UcharDescriptor(data, dataSize)
    {}

    static Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        std::shared_ptr<uchar_t> buffer(new uchar_t[descriptorLenght], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uint16_t lcn;  // lcn flag + lcn
        uchar_t vc;    // vc falg + vc

        data = data + ConvertHexStrToInt(data, lcn);
        data = data + ConvertHexStrToInt(data, vc);
        ptr = ptr + WriteBuffer(ptr, lcn);
        ptr = ptr + WriteBuffer(ptr, vc);

        return new UserdefinedDscriptor83(data, descriptorLenght);
    }
    uchar_t GetTag() const { return Tag; }
};

class UserdefinedDscriptor83Creator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(uchar_t *data)
    {
        uchar_t descriptorLenght;
        data = data + ConvertHexStrToInt(data, descriptorLenght);

        std::shared_ptr<uchar_t> buffer(new uchar_t[descriptorLenght], UcharDeleter());
        uchar_t *ptr = buffer.get();

        uint16_t lcn;  // lcn flag + lcn
        uchar_t vc;    // vc falg + vc

        data = data + ConvertHexStrToInt(data, lcn);
        data = data + ConvertHexStrToInt(data, vc);
        ptr = ptr + WriteBuffer(ptr, lcn);
        ptr = ptr + WriteBuffer(ptr, vc);

        return new UserdefinedDscriptor83(data, descriptorLenght);
    }

    Descriptor* CreateInstance(uchar_t *data, size_t dataSize) 
    { 
        return new UserdefinedDscriptor83(data, dataSize); 
    }
};

/**********************class Descriptors**********************/
class Descriptors: public Components
{
public:
    typedef Components MyBase;

    void AddDescriptor(uchar_t tag, uchar_t* data);
    void AddDescriptor(std::shared_ptr<Descriptor> discriptor);

    /* the following function is provided just for debug */
    void Put(std::ostream& os) const;
};

/**********************class DescriptorFactory**********************/
class DescriptorFactory
{
public:
    /* Create descriptor from string */
    Descriptor* DescriptorFactory::Create(uchar_t tag, uchar_t *data)
    {
        auto iter = creators.find(tag);
        if (iter == creators.end())
        {
            return nullptr;
        }

        std::shared_ptr<DescriptorCreator> creator = iter->second;
        return creator->CreateInstance(data);
    }

    /* Create descriptor from binary (for example .ts file). */
    Descriptor* DescriptorFactory::Create(uchar_t tag, uchar_t *data, size_t dataSize)
    {
        auto iter = creators.find(tag);
        if (iter == creators.end())
        {
            return nullptr;
        }

        std::shared_ptr<DescriptorCreator> creator = iter->second;
        return creator->CreateInstance(data, dataSize);
    }

    void Register(uchar_t tag, std::shared_ptr<DescriptorCreator> creator)
    {
        creators.insert(make_pair(tag, creator));
    }

    static DescriptorFactory& GetInstance()
    {
        static DescriptorFactory instance;
        return instance;
    }

private:
    DescriptorFactory() { /* do nothing */ }
    std::map<uchar_t, std::shared_ptr<DescriptorCreator>> creators;
};

class AutoRegisterSuite
{
public:
    AutoRegisterSuite(uchar_t tag, std::shared_ptr<DescriptorCreator> creator)
    {
        DescriptorFactory& factory = DescriptorFactory::GetInstance();
        factory.Register(tag, creator);
    }
};

#define DescriptorCreatorRegistration(tag, creator)      \
    static AutoRegisterSuite  JoinName(descriptorCreator, __LINE__)(tag, std::make_shared<creator>())

/* Create descriptor from string */
Descriptor* CreateDescriptor(uchar_t tag, uchar_t *data);

/* Create descriptor from binary (for example .ts file). */
Descriptor* CreateDescriptor(uchar_t tag, uchar_t *data, size_t dataSize);

#endif