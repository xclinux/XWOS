/**
 * @file
 * @brief C++ Literal Operator Test
 * @author
 * + 隐星魂 (Roy Sun) <xwos@xwos.tech>
 * @copyright
 * + Copyright © 2015 xwos.tech, All Rights Reserved.
 * > Licensed under the Apache License, Version 2.0 (the "License");
 * > you may not use this file except in compliance with the License.
 * > You may obtain a copy of the License at
 * >
 * >         http://www.apache.org/licenses/LICENSE-2.0
 * >
 * > Unless required by applicable law or agreed to in writing, software
 * > distributed under the License is distributed on an "AS IS" BASIS,
 * > WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * > See the License for the specific language governing permissions and
 * > limitations under the License.
 */

#include <string>
#include <cstring>
#include "test/literal.hxx"

void testLiteralOperator(void)
{
  char cstr[64];
  ::std::string cxxstr;

  cxxstr = "XuanWuOS"_s;
  strcpy(cstr, cxxstr.data());
}
