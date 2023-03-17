/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2019 RDK Management
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
**/
#pragma once
#include "Module.h"
#include<gst/gst.h>
#include<pthread.h>
                GstElement *pipeline;
                GstBus *bus;
                GstMessage *msg;
                GstEvent *event;  
                static bool looping;
namespace WPEFramework {
   namespace Plugin {
      class Player : public PluginHost::IPlugin
                     , public PluginHost::JSONRPC {
            private:
                Player(const Player&) = delete;
                Player& operator=(const Player&) = delete;
                // simple method const JsonObject& parameters, JsonObject& response
                
            public:
               Player(); 
               virtual ~Player();
                // IPlugin methods
                virtual const string Initialize(PluginHost::IShell* service) override;
                virtual void Deinitialize(PluginHost::IShell* service) override;
                virtual string Information() const override ;
                uint32_t Path(const JsonObject& request);
                uint32_t pause_play();
                uint32_t set_loop();
                BEGIN_INTERFACE_MAP(Player)
                INTERFACE_ENTRY(PluginHost::IPlugin)
                INTERFACE_ENTRY(PluginHost::IDispatcher)
                END_INTERFACE_MAP
        };
   } // namespace Plugin
} // namespace WPEFramework
