#include "VirtualDevice/VirtualDevice.h"
#include <utility>
namespace VirtualDevice {
namespace Detail {struct Device_State {std::uint64_t id=0x8000000000000001ull;};}
Device::~Device()=default;Device::Device(Device&&)noexcept=default;Device& Device::operator=(Device&&)noexcept=default;
Device::operator bool()const noexcept{return bool(state_);}std::uint64_t Device::Id()const noexcept{return state_?state_->id:0;}
Result Check(const Device_Config& c){if(c.descriptors.empty())return {87,"Missing descriptors"};return {};}
Info Status(){Info i;i.version=1;i.max_devices=16;i.max_transfer=4096;i.full_speed=true;i.trial_remaining_100ns=0x8000000000000003ull;Device_Details d;d.id=0x8000000000000001ull;d.token="fixture-\xc3\xa9";i.devices.push_back(d);return i;}
Device Connect(const Device_Config& c){Device d;if(!Check(c)){d.error=87;return d;}d.state_=std::make_shared<Detail::Device_State>();d.token="fixture-\xc3\xa9";return d;}
Result Disconnect(Device& d){d.state_.reset();return {};}
Result Send(const Device& d,std::uint8_t endpoint,const std::vector<std::uint8_t>& bytes){if(!d)return {6,"No device"};if(endpoint!=0x81 || bytes.size()!=3 || bytes.data()[2]!=255)return {87,"Payload mismatch"};return {};}
Output Receive(std::uint32_t timeout){Output o;if(timeout==100){o.timed_out=true;return o;}o.kind=Output_Kind::Control;o.device_id=0x8000000000000001ull;o.request_id=0x8000000000000002ull;o.device_token="fixture-\xc3\xa9";o.data={0,1,255};return o;}
Result Reply(const Output& output,const std::vector<std::uint8_t>& bytes,bool stall){if(output.request_id!=0x8000000000000002ull || bytes.size()!=3 || stall)return {87,"Reply mismatch"};return {};}
}
