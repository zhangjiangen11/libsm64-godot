#include <sm64_surface_properties.hpp>

#include <godot_cpp/core/class_db.hpp>


#define SURFACE_TYPE_HINT_STRING "Default,Burning,0004,Hangable,Slow,Death Plane,Close Camera,Water,Flowing Water,Intangible,Very Slippery,Slippery,Not Slippery,Ttm Vines,Mgr Music,Instant Warp 1b,Instant Warp 1c,Instant Warp 1d,Instant Warp 1e,Shallow Quicksand,Deep Quicksand,Instant Quicksand,Deep Moving Quicksand,Shallow Moving Quicksand,Quicksand,Moving Quicksand,Wall Misc,Noise Default,Noise Slippery,Horizontal Wind,Instant Moving Quicksand,Ice,Look Up Warp,Hard,Warp,Timer Start,Timer End,Hard Slippery,Hard Very Slippery,Hard Not Slippery,Vertical Wind,Boss Fight Camera,Camera Free Roam,Thi3 Wallkick,Camera 8 Dir,Camera Middle,Camera Rotate Right,Camera Rotate Left,Camera Boundary,Noise Very Slippery 73,Noise Very Slippery 74,Noise Very Slippery,No Cam Collision,No Cam Collision 77,No Cam Col Very Slippery,No Cam Col Slippery,Switch,Vanish Cap Walls,Painting Wobble A6,Painting Wobble A7,Painting Wobble A8,Painting Wobble A9,Painting Wobble Aa,Painting Wobble Ab,Painting Wobble Ac,Painting Wobble Ad,Painting Wobble Ae,Painting Wobble Af,Painting Wobble B0,Painting Wobble B1,Painting Wobble B2,Painting Wobble B3,Painting Wobble B4,Painting Wobble B5,Painting Wobble B6,Painting Wobble B7,Painting Wobble B8,Painting Wobble B9,Painting Wobble Ba,Painting Wobble Bb,Painting Wobble Bc,Painting Wobble Bd,Painting Wobble Be,Painting Wobble Bf,Painting Wobble C0,Painting Wobble C1,Painting Wobble C2,Painting Wobble C3,Painting Wobble C4,Painting Wobble C5,Painting Wobble C6,Painting Wobble C7,Painting Wobble C8,Painting Wobble C9,Painting Wobble Ca,Painting Wobble Cb,Painting Wobble Cc,Painting Wobble Cd,Painting Wobble Ce,Painting Wobble Cf,Painting Wobble D0,Painting Wobble D1,Painting Wobble D2,Painting Warp D3,Painting Warp D4,Painting Warp D5,Painting Warp D6,Painting Warp D7,Painting Warp D8,Painting Warp D9,Painting Warp Da,Painting Warp Db,Painting Warp Dc,Painting Warp Dd,Painting Warp De,Painting Warp Df,Painting Warp E0,Painting Warp E1,Painting Warp E2,Painting Warp E3,Painting Warp E4,Painting Warp E5,Painting Warp E6,Painting Warp E7,Painting Warp E8,Painting Warp E9,Painting Warp Ea,Painting Warp Eb,Painting Warp Ec,Painting Warp Ed,Painting Warp Ee,Painting Warp Ef,Painting Warp F0,Painting Warp F1,Painting Warp F2,Painting Warp F3,Ttc Painting 1,Ttc Painting 2,Ttc Painting 3,Painting Warp F7,Painting Warp F8,Painting Warp F9,Painting Warp Fa,Painting Warp Fb,Painting Warp Fc,Wobbling Warp,Trapdoor"
#define TERRAIN_TYPE_HINT_STRING "Grass,Stone,Snow,Sand,Spooky,Water,Slide,Mask"


void SM64SurfaceProperties::set_surface_type(SurfaceType value)
{
    surface_type = value;
}

SM64SurfaceProperties::SurfaceType SM64SurfaceProperties::get_surface_type() const
{
    return surface_type;
}

void SM64SurfaceProperties::set_terrain_type(TerrainType value)
{
    terrain_type = value;
}

SM64SurfaceProperties::TerrainType SM64SurfaceProperties::get_terrain_type() const
{
    return terrain_type;
}

void SM64SurfaceProperties::set_force(int value)
{
    force = value;
}

int SM64SurfaceProperties::get_force() const
{
    return force;
}

void SM64SurfaceProperties::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("set_surface_type", "value"), &SM64SurfaceProperties::set_surface_type);
    godot::ClassDB::bind_method(godot::D_METHOD("get_surface_type"), &SM64SurfaceProperties::get_surface_type);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "surface_type", godot::PROPERTY_HINT_ENUM, SURFACE_TYPE_HINT_STRING), "set_surface_type", "get_surface_type");
    godot::ClassDB::bind_method(godot::D_METHOD("set_terrain_type", "value"), &SM64SurfaceProperties::set_terrain_type);
    godot::ClassDB::bind_method(godot::D_METHOD("get_terrain_type"), &SM64SurfaceProperties::get_terrain_type);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "terrain_type", godot::PROPERTY_HINT_ENUM, TERRAIN_TYPE_HINT_STRING), "set_terrain_type", "get_terrain_type");
    godot::ClassDB::bind_method(godot::D_METHOD("set_force", "value"), &SM64SurfaceProperties::set_force);
    godot::ClassDB::bind_method(godot::D_METHOD("get_force"), &SM64SurfaceProperties::get_force);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "force"), "set_force", "get_force");

    BIND_ENUM_CONSTANT(SURFACE_TYPE_DEFAULT);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_BURNING);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_0004);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_HANGABLE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_SLOW);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_DEATH_PLANE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CLOSE_CAMERA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_WATER);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_FLOWING_WATER);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INTANGIBLE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_VERY_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NOT_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TTM_VINES);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_MGR_MUSIC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INSTANT_WARP_1B);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INSTANT_WARP_1C);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INSTANT_WARP_1D);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INSTANT_WARP_1E);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_SHALLOW_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_DEEP_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INSTANT_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_DEEP_MOVING_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_SHALLOW_MOVING_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_MOVING_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_WALL_MISC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NOISE_DEFAULT);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NOISE_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_HORIZONTAL_WIND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_INSTANT_MOVING_QUICKSAND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_ICE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_LOOK_UP_WARP);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_HARD);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_WARP);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TIMER_START);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TIMER_END);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_HARD_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_HARD_VERY_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_HARD_NOT_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_VERTICAL_WIND);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_BOSS_FIGHT_CAMERA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CAMERA_FREE_ROAM);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_THI3_WALLKICK);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CAMERA_8_DIR);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CAMERA_MIDDLE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CAMERA_ROTATE_RIGHT);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CAMERA_ROTATE_LEFT);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_CAMERA_BOUNDARY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NOISE_VERY_SLIPPERY_73);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NOISE_VERY_SLIPPERY_74);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NOISE_VERY_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NO_CAM_COLLISION);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NO_CAM_COLLISION_77);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NO_CAM_COL_VERY_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_NO_CAM_COL_SLIPPERY);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_SWITCH);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_VANISH_CAP_WALLS);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_A6);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_A7);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_A8);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_A9);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_AA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_AB);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_AC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_AD);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_AE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_AF);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B0);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B1);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B2);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B3);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B4);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B5);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B6);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B7);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B8);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_B9);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_BA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_BB);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_BC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_BD);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_BE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_BF);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C0);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C1);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C2);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C3);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C4);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C5);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C6);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C7);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C8);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_C9);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_CA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_CB);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_CC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_CD);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_CE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_CF);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_D0);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_D1);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WOBBLE_D2);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D3);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D4);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D5);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D6);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D7);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D8);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_D9);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_DA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_DB);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_DC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_DD);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_DE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_DF);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E0);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E1);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E2);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E3);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E4);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E5);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E6);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E7);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E8);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_E9);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_EA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_EB);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_EC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_ED);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_EE);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_EF);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F0);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F1);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F2);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F3);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TTC_PAINTING_1);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TTC_PAINTING_2);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TTC_PAINTING_3);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F7);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F8);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_F9);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_FA);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_FB);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_PAINTING_WARP_FC);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_WOBBLING_WARP);
    BIND_ENUM_CONSTANT(SURFACE_TYPE_TRAPDOOR);

    BIND_ENUM_CONSTANT(TERRAIN_TYPE_GRASS);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_STONE);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_SNOW);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_SAND);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_SPOOKY);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_WATER);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_SLIDE);
    BIND_ENUM_CONSTANT(TERRAIN_TYPE_MASK);
}
