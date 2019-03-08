/*
  Package Object : An interface of Data that is to be passed between a Server and a Client
  Author: Rafid Siddiqui
*/
#include <iostream>
#include <string>

using namespace std;

class Package
{

private:
    string msg_;
    string status_;
    string time_;

public:

    Package() {}
    Package(string msg,string status,string time):msg_(msg),status_(status),time_(time) {}

    string get_msg() {
        return msg_;
    }
    string get_status() {
        return status_;
    }
    string get_time() {
        return time_;
    }

    string set_msg(string msg) {
        msg_=msg;
    }
    string set_status(string status) {
        status_=status;
    }
    string set_time(string time) {
        time_=time;
    }



    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & msg_;
        ar & status_;
        ar & time_;

    }

};
