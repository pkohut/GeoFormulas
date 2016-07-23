/** \file RNavConversionException.h
*   \brief
*/

/****************************************************************************/
/*  RNavConversionException.h                                               */
/****************************************************************************/
/*                                                                          */
/*  Copyright 2008 - 2016 Paul Kohut                                        */
/*  Licensed under the Apache License, Version 2.0 (the "License"); you may */
/*  not use this file except in compliance with the License. You may obtain */
/*  a copy of the License at                                                */
/*                                                                          */
/*  http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or         */
/*  implied. See the License for the specific language governing            */
/*  permissions and limitations under the License.                          */
/*                                                                          */
/****************************************************************************/

#pragma once

#include <iostream>
#include <exception>

class CRNavConversionException : public std::exception {
public:
    //  CRNavConversionException(void) {}
    CRNavConversionException(std::string sEx) : m_sEx(sEx)
    { }

    virtual ~CRNavConversionException(void)
    { }

    const char *what() const throw()
    { return m_sEx.c_str(); }

    std::string m_sEx;
};
