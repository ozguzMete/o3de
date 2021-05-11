/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzNetworking/Serialization/ISerializer.h>
#include <AzCore/std/containers/map.h>

namespace AzNetworking
{
    // StringifySerializer
    // Generate a debug string of a serializable object
    class StringifySerializer
        : public ISerializer
    {
    public:

        using StringMap = AZStd::map<AZStd::string, AZStd::string>;

        StringifySerializer(char delimeter = ' ', bool outputFieldNames = true, const AZStd::string& seperator = "=");

        // GetString
        // After serializing objects, get the serialized values as a single string
        const AZStd::string& GetString() const;

        // GetValueMap
        // After serializing objects, get the serialized values as key value pairs
        const StringMap& GetValueMap() const;

        // ISerializer interfaces
        SerializerMode GetSerializerMode() const override;
        bool Serialize(bool& value, const char* name) override;
        bool Serialize(char& value, const char* name, char minValue, char maxValue) override;
        bool Serialize(int8_t& value, const char* name, int8_t minValue, int8_t maxValue) override;
        bool Serialize(int16_t& value, const char* name, int16_t minValue, int16_t maxValue) override;
        bool Serialize(int32_t& value, const char* name, int32_t minValue, int32_t maxValue) override;
        bool Serialize(int64_t& value, const char* name, int64_t minValue, int64_t maxValue) override;
        bool Serialize(uint8_t& value, const char* name, uint8_t minValue, uint8_t maxValue) override;
        bool Serialize(uint16_t& value, const char* name, uint16_t minValue, uint16_t maxValue) override;
        bool Serialize(uint32_t& value, const char* name, uint32_t minValue, uint32_t maxValue) override;
        bool Serialize(uint64_t& value, const char* name, uint64_t minValue, uint64_t maxValue) override;
        bool Serialize(float& value, const char* name, float minValue, float maxValue) override;
        bool Serialize(double& value, const char* name, double minValue, double maxValue) override;
        bool SerializeBytes(uint8_t* buffer, uint32_t bufferCapacity, bool isString, uint32_t& outSize, const char* name) override;
        bool BeginObject(const char* name, const char* typeName) override;
        bool EndObject(const char* name, const char* typeName) override;

        const uint8_t* GetBuffer() const override;
        uint32_t GetCapacity() const override;
        uint32_t GetSize() const override;
        void ClearTrackedChangesFlag() override {}
        bool GetTrackedChangesFlag() const override { return false; }
        // ISerializer interfaces

    private:

        template <typename T>
        bool ProcessData(const char* name, const T& value);

    private:

        char m_delimeter;
        bool m_outputFieldNames = true;

        StringMap m_map;
        AZStd::string m_string;
        AZStd::string m_prefix;
        AZStd::string m_separator;
        AZStd::deque<AZStd::size_t> m_prefixSizeStack;
    };
}