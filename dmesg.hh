/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef DMESG_HH_4274946366__H_
#define DMESG_HH_4274946366__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

namespace c {
struct pci_desc {
    std::string bus;
    std::string recource;
    std::string memory;
    pci_desc() :
        bus(std::string()),
        recource(std::string()),
        memory(std::string())
        { }
};

struct avro_dmesg_json_Union__0__ {
private:
    size_t idx_;
    boost::any value_;
public:
    size_t idx() const { return idx_; }
    std::string get_string() const;
    void set_string(const std::string& v);
    pci_desc get_pci_desc() const;
    void set_pci_desc(const pci_desc& v);
    avro_dmesg_json_Union__0__();
};

struct dmesg_parse {
    typedef avro_dmesg_json_Union__0__ description_t;
    std::string time_label;
    std::string group;
    description_t description;
    dmesg_parse() :
        time_label(std::string()),
        group(std::string()),
        description(description_t())
        { }
};

inline
std::string avro_dmesg_json_Union__0__::get_string() const {
    if (idx_ != 0) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<std::string >(value_);
}

inline
void avro_dmesg_json_Union__0__::set_string(const std::string& v) {
    idx_ = 0;
    value_ = v;
}

inline
pci_desc avro_dmesg_json_Union__0__::get_pci_desc() const {
    if (idx_ != 1) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<pci_desc >(value_);
}

inline
void avro_dmesg_json_Union__0__::set_pci_desc(const pci_desc& v) {
    idx_ = 1;
    value_ = v;
}

inline avro_dmesg_json_Union__0__::avro_dmesg_json_Union__0__() : idx_(0), value_(std::string()) { }
}
namespace avro {
template<> struct codec_traits<c::pci_desc> {
    static void encode(Encoder& e, const c::pci_desc& v) {
        avro::encode(e, v.bus);
        avro::encode(e, v.recource);
        avro::encode(e, v.memory);
    }
    static void decode(Decoder& d, c::pci_desc& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.bus);
                    break;
                case 1:
                    avro::decode(d, v.recource);
                    break;
                case 2:
                    avro::decode(d, v.memory);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.bus);
            avro::decode(d, v.recource);
            avro::decode(d, v.memory);
        }
    }
};

template<> struct codec_traits<c::avro_dmesg_json_Union__0__> {
    static void encode(Encoder& e, c::avro_dmesg_json_Union__0__ v) {
        e.encodeUnionIndex(v.idx());
        switch (v.idx()) {
        case 0:
            avro::encode(e, v.get_string());
            break;
        case 1:
            avro::encode(e, v.get_pci_desc());
            break;
        }
    }
    static void decode(Decoder& d, c::avro_dmesg_json_Union__0__& v) {
        size_t n = d.decodeUnionIndex();
        if (n >= 2) { throw avro::Exception("Union index too big"); }
        switch (n) {
        case 0:
            {
                std::string vv;
                avro::decode(d, vv);
                v.set_string(vv);
            }
            break;
        case 1:
            {
                c::pci_desc vv;
                avro::decode(d, vv);
                v.set_pci_desc(vv);
            }
            break;
        }
    }
};

template<> struct codec_traits<c::dmesg_parse> {
    static void encode(Encoder& e, const c::dmesg_parse& v) {
        avro::encode(e, v.time_label);
        avro::encode(e, v.group);
        avro::encode(e, v.description);
    }
    static void decode(Decoder& d, c::dmesg_parse& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.time_label);
                    break;
                case 1:
                    avro::decode(d, v.group);
                    break;
                case 2:
                    avro::decode(d, v.description);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.time_label);
            avro::decode(d, v.group);
            avro::decode(d, v.description);
        }
    }
};

}
#endif
