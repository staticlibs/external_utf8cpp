/*
 * Copyright 2018, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   utf8cpp_test.cpp
 * Author: alex
 *
 * Created on May 15, 2018, 9:23 PM
 */

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "utf8.h"

#include "staticlib/config/assert.hpp"

void test_utf16() {
    auto u8src = std::string("\xd0\xbf\xd1\x80\xd0\xb8\xd0\xb2\xd0\xb5\xd1\x82");
    auto u16src = std::vector<uint16_t>();
    u16src.push_back(0x043f);
    u16src.push_back(0x0440);
    u16src.push_back(0x0438);
    u16src.push_back(0x0432);
    u16src.push_back(0x0435);
    u16src.push_back(0x0442);

    // 8 to 16
    auto u16dest = std::vector<uint16_t>();
    utf8::utf8to16(u8src.begin(), u8src.end(), std::back_inserter(u16dest));
    slassert(u16src.size() == u16dest.size());
    for (size_t i = 0; i < u16src.size(); i++) {
        slassert(u16src.at(i) == u16dest.at(i));
    }

    // 16 to 8
    auto u8dest = std::string();
    utf8::utf16to8(u16src.begin(), u16src.end(), std::back_inserter(u8dest));
    slassert(u8src.length() == u8dest.length());
    for (size_t i = 0; i < u8src.length(); i++) {
        slassert(u8src.at(i) == u8dest.at(i));
    }
}

int main() {
    try {
        test_utf16();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
