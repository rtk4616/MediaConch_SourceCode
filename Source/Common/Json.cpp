/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//---------------------------------------------------------------------------
#ifdef HAVE_JANSSON

//---------------------------------------------------------------------------
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

//---------------------------------------------------------------------------
#include "Json.h"
#include <sstream>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
namespace MediaConch {

//***************************************************************************
// Json
//***************************************************************************

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Json::Json() : current_node(NULL)
{
}

//---------------------------------------------------------------------------
Json::~Json()
{
}

//---------------------------------------------------------------------------
int Json::parse(const std::string& data, Value &v)
{
    json_error_t err;
    json_t       *elements = NULL;

    elements = json_loads(data.c_str(), 0, &err);

    if (!elements)
    {
        std::stringstream ss;
        if (err.line >= 0)
            ss << "line " << err.line << ": ";
        ss << err.text;
        error = ss.str();
        return -1;
    }
    current_node = elements;

    int ret = parse_node(v);
    json_decref(elements);
    current_node = NULL;
    return ret;
}

//---------------------------------------------------------------------------
int Json::serialize(Value &v, std::string& data)
{
    json_t *j = serialize_node(v);
    if (!j)
    {
        error = std::string("cannot serialize the node");
        return -1;
    }

    std::string ret;
    char *json = json_dumps(j, JSON_ENCODE_ANY);

    data = std::string(json);
    free(json);
    json_decref(j);

    return 0;
}

//---------------------------------------------------------------------------
Container::Value* Json::get_value_by_key(Value& v, const std::string& key)
{
    if (v.type != Value::CONTAINER_TYPE_OBJECT)
        return NULL;

    if (v.obj.find(key) != v.obj.end())
        return &v.obj[key];
    return NULL;
}

//---------------------------------------------------------------------------
Container::Value* Json::get_value_in_array_by_key(Value& v, const std::string& key)
{
    if (v.type != Value::CONTAINER_TYPE_ARRAY)
        return NULL;

    for (size_t i = 0; i < v.array.size(); ++i)
    {
        Container::Value* val = get_value_by_key(v.array[i], key);
        if (val)
            return val;
    }
    return NULL;
}

//---------------------------------------------------------------------------
int Json::get_type_node(Value &v)
{
    switch (json_typeof(current_node))
    {
        case JSON_INTEGER:
            v.type = Value::CONTAINER_TYPE_INTEGER;
            v.l = json_integer_value(current_node);
            break;
        case JSON_REAL:
            v.type = Value::CONTAINER_TYPE_REAL;
            v.d = json_real_value(current_node);
            break;
        case JSON_STRING:
            v.type = Value::CONTAINER_TYPE_STRING;
            v.s = json_string_value(current_node);
            break;
        case JSON_TRUE:
            v.type = Value::CONTAINER_TYPE_BOOL;
            v.b = true;
            break;
        case JSON_FALSE:
            v.type = Value::CONTAINER_TYPE_BOOL;
            v.b = false;
            break;
        case JSON_NULL:
            v.type = Value::CONTAINER_TYPE_NULL;
            break;
        default:
            return -1;
    }
    return 0;
}

//---------------------------------------------------------------------------
int Json::parse_node(Value &v)
{
    if (!current_node)
        return -1;

    if (!get_type_node(v))
        return 0;

    if (json_is_object(current_node))
    {
        v.type = Value::CONTAINER_TYPE_OBJECT;

        const char *key = NULL;
        json_t *value = NULL;
        json_object_foreach(current_node, key, value) {
            Value new_node;
            json_t *tmp = current_node;
            current_node = value;

            if (parse_node(new_node))
                return -1;

            v.obj[std::string(key)] = new_node;
            current_node = tmp;
        }
        return 0;
    }

    if (json_is_array(current_node))
    {
        v.type = Value::CONTAINER_TYPE_ARRAY;
        for (size_t i = 0; i < json_array_size(current_node); ++i)
        {
            Value new_node;
            json_t *tmp = current_node;

            current_node = json_array_get(current_node, i);
            if (parse_node(new_node))
                return -1;
            v.array.push_back(new_node);
            current_node = tmp;
        }
        return 0;
    }

    return -1;
}

//---------------------------------------------------------------------------
json_t *Json::set_basic_node(Value &v)
{
    switch (v.type)
    {
        case Value::CONTAINER_TYPE_INTEGER:
            return json_integer(v.l);
        case Value::CONTAINER_TYPE_REAL:
            return json_real(v.d);
        case Value::CONTAINER_TYPE_STRING:
            return json_string(v.s.c_str());
        case Value::CONTAINER_TYPE_BOOL:
            if (v.b == true)
                return json_true();
            return json_false();
        case Value::CONTAINER_TYPE_NULL:
            return json_null();
        default:
            break;
    }
    return NULL;
}

//---------------------------------------------------------------------------
json_t *Json::serialize_node(Value &v)
{
    json_t *tmp = NULL;
    if ((tmp = set_basic_node(v)))
        return tmp;

    if (v.type == Value::CONTAINER_TYPE_OBJECT)
    {
        tmp = json_object();
        std::map<std::string, Container::Value>::iterator it = v.obj.begin();
        for (; it != v.obj.end(); ++it)
        {
            json_t *node = serialize_node(it->second);
            if (!node)
                return NULL;

            if (json_object_set_new(tmp, it->first.c_str(), node))
                return NULL;
        }
        return tmp;
    }

    if (v.type == Value::CONTAINER_TYPE_ARRAY)
    {
        tmp = json_array();
        for (size_t i = 0; i < v.array.size(); ++i)
        {
            json_t *node = serialize_node(v.array[i]);
            if (!node)
                return NULL;
            if (json_array_append_new(tmp, node))
                return NULL;
        }
        return tmp;
    }

    return NULL;
}

}

#endif // !HAVE_JANSSON
