#ifndef _Descriptor_h_
#define _Descriptor_h_

/**********************class Descriptor**********************/
class Descriptor
{
public:  
    Descriptor(uchar_t *theData);
    virtual ~Descriptor();

    size_t GetCodesSize() const;
    uchar_t GetTag() const;
    size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const;

private:
    uchar_t *data;
};

/**********************class DescriptorCreator**********************/
class DescriptorCreator
{
public:
    DescriptorCreator();
    virtual ~DescriptorCreator();

    /* Create descriptor from string. */
    virtual Descriptor* CreateInstance(std::string &strData);

    /* Create descriptor from binary (for example .ts file). */
    virtual Descriptor* CreateInstance(uchar_t *data);
};

/**********************class NetworkNameDescriptor**********************/
/* network_name_descriptor */
class NetworkNameDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x40};
    NetworkNameDescriptor(uchar_t *data);
};

class NetworkNameDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class ServiceListDescriptor**********************/
/* service_list_descriptor 
service_list_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    for (i=0;i<N;I++)
    {
        service_id 16 uimsbf
        service_type 8 uimsbf
    }
}
 */
class ServiceListDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x41};
    ServiceListDescriptor(uchar_t *data);
};

class ServiceListDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data) ;
};

/**********************class StuffingDescriptor**********************/
/* stuffing_descriptor */
class StuffingDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x42};
    StuffingDescriptor(uchar_t *data);
};

class StuffingDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class SatelliteDeliverySystemDescriptor**********************/
/* satellite_delivery_system_descriptor */
class SatelliteDeliverySystemDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x43};
    SatelliteDeliverySystemDescriptor(uchar_t *data);
};

class SatelliteDeliverySystemDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class CableDeliverySystemDescriptor**********************/
/* cable_delivery_system_descriptor  
cable_delivery_system_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    frequency 32 bslbf
    reserved_future_use 12 bslbf
    FEC_outer 4 bslbf
    modulation 8 bslbf
    symbol_rate 28 bslbf
    FEC_inner 4 bslbf
}
 */
class CableDeliverySystemDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x44};
    CableDeliverySystemDescriptor(uchar_t *data);
};

class CableDeliverySystemDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class BouquetNameDescriptor**********************/
/* bouquet_name_descriptor 
bouquet_name_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    for(i=0;i<N;i++)
    {
        char 8 uimsbf
    }
}
 */
class BouquetNameDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x47};
    BouquetNameDescriptor(uchar_t *data);
};

class BouquetNameDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class ServiceDescriptor**********************/
/* service_descriptor  */
/*
service_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    service_type 8 uimsbf
    service_provider_name_length 8 uimsbf
    for (i=0;i<N;I++)
    {
        char 8 uimsbf
    }
    service_name_length 8 uimsbf
    for (i=0;i<N;I++)
    {
        char 8 uimsbf
    }
}
 */
class ServiceDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x48};
    ServiceDescriptor(uchar_t *data);
};

class ServiceDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class LinkageDescriptor**********************/
/* linkage_descriptor. */
class LinkageDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x4A};
    LinkageDescriptor(uchar_t *data);
};

class LinkageDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class NvodReferenceDescriptor**********************/
/* 
NVOD_reference_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    for (i=0;i<N;i++) 
    {
        transport_stream_id 16 uimsbf
        original_network_id 16 uimsbf
        service_id 16 uimsbf
    }
}
*/
class NvodReferenceDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x4B};
    NvodReferenceDescriptor(uchar_t *data);
};

class NvodReferenceDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class TimeShiftedServiceDescriptor**********************/
/*
time_shifted_service_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    reference_service_id 16 uimsbf
}
*/
class TimeShiftedServiceDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x4C};
    TimeShiftedServiceDescriptor(uchar_t *data);
};

class TimeShiftedServiceDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class ShortEventDescriptor**********************/
/* short_event_descriptor 
short_event_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    ISO_639_language_code 24 bslbf
    event_name_length 8 uimsbf
    for (i=0;i<event_name_length;i++)
    {
        event_name_char 8 uimsbf
    }
    text_length 8 uimsbf
    for (i=0;i<text_length;i++)
    {
        text_char 8 uimsbf
    }
}
 */
class ShortEventDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x4D};
    ShortEventDescriptor(uchar_t *data);
};

class ShortEventDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class ExtendedEventDescriptor**********************/
/* extended_event_descriptor */
class ExtendedEventDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x4E};
    ExtendedEventDescriptor(uchar_t *data);
};

class ExtendedEventDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class TimeShiftedEventDescriptor**********************/
/* time_shifted_event_descriptor 
time_shifted_event_descriptor()
{
    descriptor_tag 8 uimsbf
    descriptor_length 8 uimsbf
    reference_service_id 16 uimsbf
    reference_event_id 16 uimsbf
}
*/
class TimeShiftedEventDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x4F};
    TimeShiftedEventDescriptor(uchar_t *data);
};

class TimeShiftedEventDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class ComponentDescriptor**********************/
/* component_descriptor */
class ComponentDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x50};
    ComponentDescriptor(uchar_t *data);
};

class ComponentDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data) ;
};

/**********************class CaIdentifierDescriptor**********************/
/* CA_identifier_descriptor */
class CaIdentifierDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x53};
    CaIdentifierDescriptor(uchar_t *data);
};

class CaIdentifierDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class ContentDescriptor**********************/
/* content_descriptor */
class ContentDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x54};
    ContentDescriptor(uchar_t *data);
};

class ContentDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class ParentalRatingDescriptor**********************/
/* parental_rating_descriptor */
class ParentalRatingDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x55};
    ParentalRatingDescriptor(uchar_t *data);
};

class ParentalRatingDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class TerrestrialDeliverySystemDescriptor**********************/
/* terrestrial_delivery_system_descriptor */
class TerrestrialDeliverySystemDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x5A};
    TerrestrialDeliverySystemDescriptor(uchar_t *data);
};

class TerrestrialDeliverySystemDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class MultilingualNetworkNameDescriptor**********************/
/* multilingual_network_name_descriptor */
class MultilingualNetworkNameDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x5B};
    MultilingualNetworkNameDescriptor(uchar_t *data);
};

class MultilingualNetworkNameDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class MultilingualComponentDescriptor**********************/
/* multilingual_component_descriptor */
class MultilingualComponentDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x5E};
    MultilingualComponentDescriptor(uchar_t *data);
};

class MultilingualComponentDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class PrivateDataSpecifierDescriptor**********************/
/* private_data_specifier_descriptor  */
class PrivateDataSpecifierDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x5F};
    PrivateDataSpecifierDescriptor(uchar_t *data);
};

class PrivateDataSpecifierDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data) ;
};

/**********************class FrequencyListDescriptor**********************/
/* frequency_list_descriptor  */
class FrequencyListDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x62};
    FrequencyListDescriptor(uchar_t *data);
};

class FrequencyListDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class DataBroadcastDescriptor**********************/
/* data_broadcast_descriptor  */
class DataBroadcastDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x64};
    DataBroadcastDescriptor(uchar_t *data);
};

class DataBroadcastDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class ExtensionDescriptor**********************/
/* extension descriptor  */
class ExtensionDescriptor: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x7F};
    ExtensionDescriptor(uchar_t *data);
};

class ExtensionDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class UserdefinedDscriptor83**********************/
/* user defined dscriptor, LCN 和音量补偿  */
class UserdefinedDscriptor83: public Descriptor
{
public: 
    enum: uchar_t {Tag  = 0x83};
    UserdefinedDscriptor83(uchar_t *data);
};

class UserdefinedDscriptor83Creator: public DescriptorCreator
{
public: 
    Descriptor * CreateInstance(std::string &strData);
    Descriptor * CreateInstance(uchar_t *data);
};

/**********************class UndefinedDescriptor**********************/
/* user defined dscriptor, both tag and data are undefined  */
class UndefinedDescriptor: public Descriptor
{
public:
    UndefinedDescriptor(uchar_t *data);
};

class UndefinedDescriptorCreator: public DescriptorCreator
{
public: 
    Descriptor* CreateInstance(std::string &strData);
    Descriptor* CreateInstance(uchar_t *data);
};

/**********************class Descriptors**********************/
class Descriptors
{
public:
    Descriptors();
    ~Descriptors();

    void AddDescriptor(Descriptor *discriptor);    
    size_t GetCodesSize() const;
    size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const;

    /* the following function is provided just for debug */
    //void Put(std::ostream& os) const;

private:
    std::list<Descriptor *> descriptors;
};

/**********************class DescriptorFactory**********************/
class DescriptorFactory
{
public:
    /* Create descriptor from string */
    Descriptor* Create(std::string &data);
    /* Create descriptor from binary (for example .ts file). */
    Descriptor* Create(uchar_t *data);
    void Register(uchar_t tag, DescriptorCreator* creator);

    static DescriptorFactory & GetInstance()
    {
        static DescriptorFactory instance;
        return instance;
    }

private:
    DescriptorFactory() { /* do nothing */ }
    std::map<uchar_t, DescriptorCreator*> creators;
};

/**********************class AutoRegisterSuite**********************/
class AutoRegisterSuite
{
public:
    AutoRegisterSuite(uchar_t tag, DescriptorCreator *creator);
};

#define DescriptorCreatorRegistration(tag, creator)      \
    static AutoRegisterSuite  JoinName(descriptorCreator, __LINE__)(tag, new creator)

/* Create descriptor from string */
Descriptor* CreateDescriptor(std::string &data);

/* Create descriptor from binary (for example .ts file). */
Descriptor* CreateDescriptor(uchar_t *data);

#endif