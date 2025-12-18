# CESE
A multiplayer deathmatch game I started developing a game in 2023 and spent one whole year working on it

## Features
* Singleplayer walking around in the map
* Type a nickname and server ip to join multiplayer
* Basic shooting system
* Start a local server
* Settings
  * Change resolution and vsync
  * Add crosshair profiles and edit them
  * Edit sensitivity

## Roadmap
- [ ] Multi-Language Support
- [ ] Add weapon models and animations
- [ ] Improve character models

## Built With
* C++
* DirectX 9
* [nlohmann_json][nlohmann-json-url]

## Installation
1- Install DirectX SDK from Microsoft
  [DirectX SDK][directx-sdk-url] <br><br>
2- Clone this repo
```sh
git clone https://github.com/aliosmansahin/cpp-cese.git
```
3- Open the solution and built it

## Starting Local Server
1- Locate folder <br>
  [Server][server-folder-url] <br><br>
2- Run .bat file which runs ["CESE Server.py"][server-file-url] <br>
  [Run This File][run-start-server-url] <br><br>




<!-- LINKS -->
[directx-sdk-url]: https://www.microsoft.com/en-us/download/details.aspx?id=6812
[server-folder-url]: https://github.com/aliosmansahin/cpp-cese/tree/bcab67358a5f3a1c342d77c3303e20d70d4d0a00/Server
[run-start-server-url]: https://github.com/aliosmansahin/cpp-cese/blob/bcab67358a5f3a1c342d77c3303e20d70d4d0a00/Server/Sunucuyu%20Baslat.bat
[server-file-url]: https://github.com/aliosmansahin/cpp-cese/blob/bcab67358a5f3a1c342d77c3303e20d70d4d0a00/Server/CESE%20Server.py
[nlohmann-json-url]: https://github.com/nlohmann/json
