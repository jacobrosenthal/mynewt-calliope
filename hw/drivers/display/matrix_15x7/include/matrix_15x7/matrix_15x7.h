/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef MYPROJ_M7X15_H
#define MYPROJ_M7X15_H

#include <stdio.h>
#include <stdint.h>
#include <nrf51.h>

extern int m15x7_init();
extern int m15x7_pixel(uint8_t x, uint8_t y, uint8_t power);
extern int m15x7_clear(void);
extern int m15x7_print_char(char ch, uint8_t ix);
extern int m15x7_print_string(char* text);

#endif