# DMC :
A 2D beat-them-all in a medievalo-steampunko-fantasy world.

Inspiration : [Cadillacs & Dinosaurs], [Dungeons & Dragons - Shadow over Mystara] and [Metal Slug X].

[Cadillacs & Dinosaurs]: https://www.youtube.com/watch?v=OHDQGuDxVUg
[Dungeons & Dragons - Shadow over Mystara]: https://www.youtube.com/watch?v=ntqBsj_h4u4
[Metal Slug X]: https://www.youtube.com/watch?v=sfParGc8BJw

## Dependencies :
- [SFML] : ```sudo apt-get install libsfml-dev```
- [Yaml-cpp] :	```sudo apt-get install libyaml-cpp-dev```
  * [!!] You could have a boost dependency missing for yaml-cpp, just do : ```sudo apt-get install libboost-dev```
  
[SFML]: http://www.sfml-dev.org
[Yaml-cpp]: https://github.com/jbeder/yaml-cpp

## Project structure :
- src : *.cpp,
- inc : *.hpp,
- obj : *.o (created after compilation),
- res :
	- sprites : all the sprites used,
	- levels : yaml file which discribe a level,
	- fonts : all the fonts used.

## Run
* To compile, type ```make```
* To compile & launch ```make l```
* To launch it in valgrind ```make v```
