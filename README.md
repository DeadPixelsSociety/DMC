# DMC :
A 2D beat-them-all in a medievalo-steampunko-fantasy world.

Inspiration :
	- [Cadillacs & Dinosaurs](https://www.youtube.com/watch?v=OHDQGuDxVUg),
	- [Dungeons & Dragons - Shadow over Mystara](https://www.youtube.com/watch?v=ntqBsj_h4u4),
	- [Metal Slug X](https://www.youtube.com/watch?v=sfParGc8BJw).

## Dependencies :
- [SFML](http://www.sfml-dev.org) :
	```
	sudo apt-get install libsfml-dev
	```
- [Yaml-cpp](https://github.com/jbeder/yaml-cpp) :
	```
	sudo apt-get install libyaml-cpp-dev
	```
  [!] You could have a boost dependency missing for yaml-cpp, just do :
	```
	sudo apt-get install libboost-dev
	```

## Project structure :
- src : *.cpp,
- inc : *.h,
- obj : *.o,
- res :
	- sprites : all the sprites used,
	- levels : yaml file which discribe a level.

## Run
To compile, type ```make```,
To compile & launch it ```make l```,
To launch it in valgrind ```make v```.
