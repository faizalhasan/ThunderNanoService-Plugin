# ThunderNanoService-Plugin
This is about implementing a new ThunderNanoservice in the WPEFramework. This plugin contains API's to play a video file. And the user gets to have the following features in the plugin:
1) Enter the path for the video file
2) Play the video
3) pause the video
4) looping  
5) Entering a new path to play video

In order to create a plugin under ThunderNanoServices. Please follow the steps below:
1) follow the steps in this repository-->https://github.com/rdkcentral/Thunder/tree/2ea26376136ab92f200a84b500ac1e64b23e9a37
2) Also in order to install Thunder tools one should clone this repository as well->https://github.com/rdkcentral/ThunderTools.git
3) Inside ThunderNanoService there will be a folder called example and under that you can add the folder called Player
4) And finally add the following line in the CMakeLists.txt file which is inside the example folder
   
  
  option(PLUGIN_PLAYER "Include Player plugin" OFF)
  
  if (PLUGIN_PLAYER)
    add_subdirectory(Player)
  endif()   
  
  
using the following curl commands the API's can be invoked:

$curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0",  "id": 42,  "method": "Player.1.Path","params":{"url":"path_to_file"}}'  http://127.0.0.1:55555/jsonrpc


$curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0",  "id": 42,  "method": "Player.1.pause_play"}'  http://127.0.0.1:55555/jsonrpc

$curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0",  "id": 42,  "method": "Player.1.set_loop"}'  http://127.0.0.1:55555/jsonrpc
