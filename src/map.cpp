#include <libsnake/map.h>

#include <map>

#include <libsnake/maps/arcade_maze.h>
#include <libsnake/maps/empty.h>
#include <libsnake/maps/standard.h>

using namespace ls::map;

static ls::map::Standard standard;
static ls::map::Empty empty;
static ls::map::ArcadeMaze arcadeMaze;
/*static ls::map::Royale royale;
static ls::map::SoloMaze soloMaze;
static ls::map::HzInnerWall hzInnerWall;
static ls::map::HzRings hzRings;
static ls::map::HzColumns hzColumns;
static ls::map::HzRiversBridges hzRiversBridges;
static ls::map::HzSpiral hzSpiral;
static ls::map::HzScatter hzScatter;
static ls::map::HzGrowBox hzGrowBox;
static ls::map::HzExpandBox hzExpandBox;
static ls::map::HzExpandScatter hzExpandScatter;*/

const Map *ls::map::getMap(const std::string &name) {
	static const std::map<std::string, Map const *> maps{
		{"standard", &standard}, {"empty", &empty}, {"arcade_maze", &arcadeMaze},
		/*{"royale", &royale},
		{"solo_maze", &soloMaze},
		{"hz_inner_wall", &hzInnerWall},
		{"hz_rings", &hzRings},
		{"hz_columns", &hzColumns},
		{"hz_rivers_bridges", &hzRiversBridges},
		{"hz_spiral", &hzSpiral},
		{"hz_scatter", &hzScatter},
		{"hz_grow_box", &hzGrowBox},
		{"hz_expand_box", &hzExpandBox},
		{"hz_expand_scatter", &hzExpandScatter},*/
	};
	auto it = maps.find(name);
	return (it == maps.end())? nullptr : (it->second);
}