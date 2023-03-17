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
#include"Player.h"
#include"bits/stdc++.h"
#include<gst/gst.h>
#include<pthread.h>
using namespace std;
namespace WPEFramework
{    
    namespace Plugin
    {
        SERVICE_REGISTRATION(Player,1,0);
        //registering the service
        Player::Player(): PluginHost::JSONRPC()
        {
          Register<JsonObject, void>(_T("Path"),&Player::Path, this);
          Register<void, void>(_T("pause_play"),&Player::pause_play, this);
        }
        Player::~Player()
        {
        }
        //for initializing the plugin
        const string Player::Initialize(PluginHost::IShell* service )
        {
         cout<<"\nit is initialized"<<endl;
         int argc=0;
         char **argv=nullptr;
         gst_init(&argc, &argv);
         return (string());
        }
        //for deinitializing the plugin if the framework is exiting
        void Player::Deinitialize(PluginHost::IShell* service )
        {
         cout<<"\nit is deinitialized"<<endl;
        }
         //for showing the information about the plugin
         /* virtual */ string Player::Information() const
         {
           return ((_T("The purpose of this plugin is provide ability to execute functional tests.")));
         } 
         
        void* bus_handler(void* arg)
        {
          bus = gst_element_get_bus (pipeline);
          while(pipeline!=NULL){
           msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
            /* Parse message */
            if (msg != NULL) {
              GError *err;
              gchar *debug_info;

              switch (GST_MESSAGE_TYPE (msg)) {
                case GST_MESSAGE_ERROR:
            gst_message_parse_error (msg, &err, &debug_info);
            g_printerr ("Error received from element %s: %s\n",
                GST_OBJECT_NAME (msg->src), err->message);
            g_printerr ("Debugging information: %s\n",
                debug_info ? debug_info : "none");
            g_clear_error (&err);
            g_free (debug_info);
            break;
                case GST_MESSAGE_EOS:
            g_print ("End-Of-Stream reached.\n");

            event = gst_event_new_seek(1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_NONE, 0);  // move the start position
                        gst_element_send_event(pipeline, event);
                        gst_element_set_state(pipeline, GST_STATE_PLAYING);
                         // Restart the pipeline
            break;
                default:
            /* We should not reach here because we only asked for ERRORs and EOS */
            g_printerr ("Unexpected message received.\n");
            break;
             }
           }
           gst_message_unref (msg);
         }
	        gst_element_set_state (pipeline, GST_STATE_NULL);
          gst_object_unref (pipeline);
	        return NULL;
        }  
      //in order to set the path of the file to play
        uint32_t Player::Path(const JsonObject& request)
        {
          uint32_t result=Core::ERROR_NONE;
          //looping=false;
          if(pipeline!=NULL)
          {
            gst_element_set_state (pipeline, GST_STATE_NULL);
            gst_object_unref (pipeline);
          }
          cout<<request["url"].String()<<endl;
          string value="playbin uri=file://";
          //value=request["url"].String();
          value.append(request["url"]);
          cout<<value<<endl;
          pipeline = gst_parse_launch(value.c_str(),NULL);
          gst_element_set_state(pipeline, GST_STATE_PLAYING); 
          pthread_t thread;   
          pthread_create(&thread, NULL, bus_handler, NULL);
          return result;
        }   
        //To pause or play the file
        uint32_t Player::pause_play()
        {
         GstState state;
         gst_element_get_state(pipeline, &state, NULL, GST_CLOCK_TIME_NONE);
         if (state == GST_STATE_PLAYING) {
             gst_element_set_state(pipeline, GST_STATE_PAUSED);
          } 
          else if (state == GST_STATE_PAUSED) {
             gst_element_set_state(pipeline, GST_STATE_PLAYING);
         } 
         return Core::ERROR_NONE;        
         }     
    }  // namespace plugin  
}  // namespace framework
