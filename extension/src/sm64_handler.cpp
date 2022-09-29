#include <sm64_handler.hpp>

#include <string>
#include <cstdio>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/array_mesh.hpp>


static void SM64DebugPrintFunction(const char *msg)
{
    godot::UtilityFunctions::print(godot::String("[libsm64] ") + godot::String(msg) + godot::String("\n"));
}

static uint8_t *utils_read_file_alloc(const char *path, size_t *fileLength)
{
    FILE *f = fopen(path, "rb");

    if (!f)
        return NULL;

    fseek(f, 0, SEEK_END);
    size_t length = (size_t)ftell(f);
    rewind(f);
    uint8_t *buffer = (uint8_t *)malloc(length + 1);
    fread(buffer, 1, length, f);
    buffer[length] = 0;
    fclose(f);

    if (fileLength)
        *fileLength = length;

    return buffer;
}

static bool check_in_bounds(real_t num)
{
    constexpr real_t bounds = 0x7FFF;
    return (num > -bounds && num < bounds);
}

static bool check_in_bounds(const godot::Vector3 &vec)
{
    return check_in_bounds(vec.x) && check_in_bounds(vec.y) && check_in_bounds(vec.z);
}

static void invert_vertex_order_2d(float *arr, size_t triangle_count)
{
    for (size_t i = 0; i < triangle_count * 6; i += 6)
    {
        float temp_x = arr[i+0];
        float temp_y = arr[i+1];
        arr[i+0] = arr[i+2];
        arr[i+1] = arr[i+3];
        arr[i+2] = temp_x;
        arr[i+3] = temp_y;
    }
}


static void invert_vertex_order_3d(float *arr, size_t triangle_count)
{
    for (size_t i = 0; i < triangle_count * 9; i += 9)
    {
        float temp_x = arr[i+0];
        float temp_y = arr[i+1];
        float temp_z = arr[i+2];
        arr[i+0] = arr[i+3];
        arr[i+1] = arr[i+4];
        arr[i+2] = arr[i+5];
        arr[i+3] = temp_x;
        arr[i+4] = temp_y;
        arr[i+5] = temp_z;
    }
}

static void invert_vertex_order(godot::PackedVector3Array &arr)
{
    for (size_t i = 0; i < arr.size() / 3; i++)
    {
        godot::Vector3 temp = arr[3*i+0];
        arr.set(3*i+0, arr[3*i+1]);
        arr.set(3*i+1, temp);
    }
}

SM64Handler::SM64Handler()
{
    mario_geometry.position = (float*) malloc(sizeof(float) * 9 * SM64_GEO_MAX_TRIANGLES);
    mario_geometry.color    = (float*) malloc(sizeof(float) * 9 * SM64_GEO_MAX_TRIANGLES);
    mario_geometry.normal   = (float*) malloc(sizeof(float) * 9 * SM64_GEO_MAX_TRIANGLES);
    mario_geometry.uv       = (float*) malloc(sizeof(float) * 6 * SM64_GEO_MAX_TRIANGLES);
}

SM64Handler::~SM64Handler()
{
    sm64_global_terminate();

    if (mario_geometry.position)
        ::free(mario_geometry.position);
    if (mario_geometry.color)
        ::free(mario_geometry.color);
    if (mario_geometry.normal)
        ::free(mario_geometry.normal);
    if (mario_geometry.uv)
        ::free(mario_geometry.uv);
}

void SM64Handler::global_init()
{
    size_t rom_size;
    uint8_t *rom = utils_read_file_alloc(rom_filename.ascii().get_data(), &rom_size);

    if (rom == NULL)
    {
        godot::UtilityFunctions::print(godot::String("[SM64Handler] Failed to read ROM file: ") + rom_filename);
        return;
    }

    uint8_t *mario_texture_raw = (uint8_t *) malloc(4 * SM64_TEXTURE_WIDTH * SM64_TEXTURE_HEIGHT);

    sm64_global_init(rom, mario_texture_raw, SM64DebugPrintFunction);

    godot::PackedByteArray mario_texture_packed;
    mario_texture_packed.resize(4 * SM64_TEXTURE_WIDTH * SM64_TEXTURE_HEIGHT);
    for (size_t i = 0; i < 4 * SM64_TEXTURE_WIDTH * SM64_TEXTURE_HEIGHT; i++)
        mario_texture_packed.set(i, mario_texture_raw[i]);
    
    mario_image.instantiate();
    mario_image->create_from_data(SM64_TEXTURE_WIDTH, SM64_TEXTURE_HEIGHT, false, godot::Image::FORMAT_RGBA8, mario_texture_packed);

    init = true;

    ::free(rom);
    ::free(mario_texture_raw);
}

bool SM64Handler::is_init() const
{
    return init;
}

godot::Ref<godot::Image> SM64Handler::get_mario_image() const
{
    return mario_image;
}

void SM64Handler::set_rom_filename(const godot::String &value)
{
    rom_filename = value;
}

godot::String SM64Handler::get_rom_filename() const
{
    return rom_filename;
}

void SM64Handler::set_scale_factor(real_t value)
{
    scale_factor = value;
}

real_t SM64Handler::get_scale_factor() const
{
    return scale_factor;
}

void SM64Handler::static_surfaces_load(godot::PackedVector3Array vertexes)
{
    struct SM64Surface *surface_array = (SM64Surface *) malloc(sizeof(SM64Surface) * vertexes.size() / 3);

    invert_vertex_order(vertexes);

    uint32_t j = 0;
    for (size_t i = 0; i < vertexes.size(); i += 3)
    {
        if (!check_in_bounds(vertexes[i] * scale_factor)
                || !check_in_bounds(vertexes[i+1] * scale_factor)
                || !check_in_bounds(vertexes[i+2] * scale_factor))
            continue;

        // TODO: export surfaces types to function argument
        surface_array[j].type = 0x0000; // SURFACE_DEFAULT
        surface_array[j].force = 0;
        surface_array[j].terrain = 0x0000; // TERRAIN_GRASS
        surface_array[j].vertices[0][0] = (int16_t) ( vertexes[i+0].z * scale_factor);
        surface_array[j].vertices[0][1] = (int16_t) ( vertexes[i+0].y * scale_factor);
        surface_array[j].vertices[0][2] = (int16_t) (-vertexes[i+0].x * scale_factor);
        surface_array[j].vertices[1][0] = (int16_t) ( vertexes[i+1].z * scale_factor);
        surface_array[j].vertices[1][1] = (int16_t) ( vertexes[i+1].y * scale_factor);
        surface_array[j].vertices[1][2] = (int16_t) (-vertexes[i+1].x * scale_factor);
        surface_array[j].vertices[2][0] = (int16_t) ( vertexes[i+2].z * scale_factor);
        surface_array[j].vertices[2][1] = (int16_t) ( vertexes[i+2].y * scale_factor);
        surface_array[j].vertices[2][2] = (int16_t) (-vertexes[i+2].x * scale_factor);

        j++;
    }

    sm64_static_surfaces_load(surface_array, j);

    ::free(surface_array);
}

int SM64Handler::mario_create(godot::Vector3 position)
{
    if (!check_in_bounds(position))
        return -2;

    int16_t x = (int16_t) ( position.z * scale_factor);
    int16_t y = (int16_t) ( position.y * scale_factor);
    int16_t z = (int16_t) (-position.x * scale_factor);
    return sm64_mario_create(x, y, z);
}

godot::Dictionary SM64Handler::mario_tick(int mario_id, godot::Ref<SM64Input> input)
{
    godot::Dictionary ret;
    godot::Array mesh_array;
    struct SM64MarioState out_state;

    godot::Vector2 cam_look = input->get_cam_look();
    godot::Vector2 stick = input->get_stick();

    struct SM64MarioInputs mario_inputs = {
        cam_look.y, // camLookX
        -cam_look.x, // camLookZ
        stick.x,
        stick.y,
        (uint8_t) input->get_a(),
        (uint8_t) input->get_b(),
        (uint8_t) input->get_z()
    };

    sm64_mario_tick(mario_id, &mario_inputs, &out_state, &mario_geometry);

    ret["position"]   = godot::Vector3(-out_state.position[2] / scale_factor, out_state.position[1] / scale_factor, out_state.position[0] / scale_factor);
    ret["velocity"]   = godot::Vector3(-out_state.velocity[2] / scale_factor, out_state.velocity[1] / scale_factor, out_state.velocity[0] / scale_factor);
    ret["face_angle"] = (real_t) godot::Math::deg2rad(out_state.faceAngle);
    ret["health"]     = (int) out_state.health;

    {
        size_t array_size = mario_geometry.numTrianglesUsed * 3;

        if (mesh_array.size() != godot::ArrayMesh::ARRAY_MAX)
            mesh_array.resize(godot::ArrayMesh::ARRAY_MAX);
        if (mario_position.size() != array_size)
            mario_position.resize(array_size);
        if (mario_normal.size() != array_size)
            mario_normal.resize(array_size);
        if (mario_color.size() != array_size)
            mario_color.resize(array_size);
        if (mario_uv.size() != array_size)
            mario_uv.resize(array_size);
    }


    invert_vertex_order_3d(mario_geometry.position, mario_geometry.numTrianglesUsed);
    invert_vertex_order_3d(mario_geometry.normal, mario_geometry.numTrianglesUsed);
    invert_vertex_order_3d(mario_geometry.color, mario_geometry.numTrianglesUsed);
    invert_vertex_order_2d(mario_geometry.uv, mario_geometry.numTrianglesUsed);

    for (int i = 0; i < mario_geometry.numTrianglesUsed; i++)
    {
        godot::Vector3 positions[3];
        positions[0].z =  mario_geometry.position[9*i+0] / scale_factor;
        positions[0].y =  mario_geometry.position[9*i+1] / scale_factor;
        positions[0].x = -mario_geometry.position[9*i+2] / scale_factor;
        positions[1].z =  mario_geometry.position[9*i+3] / scale_factor;
        positions[1].y =  mario_geometry.position[9*i+4] / scale_factor;
        positions[1].x = -mario_geometry.position[9*i+5] / scale_factor;
        positions[2].z =  mario_geometry.position[9*i+6] / scale_factor;
        positions[2].y =  mario_geometry.position[9*i+7] / scale_factor;
        positions[2].x = -mario_geometry.position[9*i+8] / scale_factor;
        mario_position.set(3*i+0, positions[0]);
        mario_position.set(3*i+1, positions[1]);
        mario_position.set(3*i+2, positions[2]);

        godot::Vector3 normals[3];
        normals[0].z =  mario_geometry.normal[9*i+0];
        normals[0].y =  mario_geometry.normal[9*i+1];
        normals[0].x = -mario_geometry.normal[9*i+2];
        normals[1].z =  mario_geometry.normal[9*i+3];
        normals[1].y =  mario_geometry.normal[9*i+4];
        normals[1].x = -mario_geometry.normal[9*i+5];
        normals[2].z =  mario_geometry.normal[9*i+6];
        normals[2].y =  mario_geometry.normal[9*i+7];
        normals[2].x = -mario_geometry.normal[9*i+8];
        mario_normal.set(3*i+0, normals[0]);
        mario_normal.set(3*i+1, normals[1]);
        mario_normal.set(3*i+2, normals[2]);

        mario_color.set(3*i+0, godot::Color(mario_geometry.color[9*i+0], mario_geometry.color[9*i+1], mario_geometry.color[9*i+2]));
        mario_color.set(3*i+1, godot::Color(mario_geometry.color[9*i+3], mario_geometry.color[9*i+4], mario_geometry.color[9*i+5]));
        mario_color.set(3*i+2, godot::Color(mario_geometry.color[9*i+6], mario_geometry.color[9*i+7], mario_geometry.color[9*i+8]));

        mario_uv.set(3*i+0, godot::Vector2(mario_geometry.uv[6*i+0], mario_geometry.uv[6*i+1]));
        mario_uv.set(3*i+1, godot::Vector2(mario_geometry.uv[6*i+2], mario_geometry.uv[6*i+3]));
        mario_uv.set(3*i+2, godot::Vector2(mario_geometry.uv[6*i+4], mario_geometry.uv[6*i+5]));
    }

    mesh_array[godot::ArrayMesh::ARRAY_VERTEX] = mario_position;
    mesh_array[godot::ArrayMesh::ARRAY_NORMAL] = mario_normal;
    mesh_array[godot::ArrayMesh::ARRAY_COLOR] = mario_color;
    mesh_array[godot::ArrayMesh::ARRAY_TEX_UV] = mario_uv;

    ret["mesh_array"] = mesh_array;

    return ret;
}

void SM64Handler::mario_delete(int mario_id)
{
    sm64_mario_delete(mario_id);
}

int SM64Handler::surface_object_create(godot::PackedVector3Array vertexes, godot::Vector3 position, godot::Vector3 rotation)
{
    struct SM64SurfaceObject surface_object;
    int id;
    struct SM64Surface *surface_array = (SM64Surface *) malloc(sizeof(SM64Surface) * vertexes.size() / 3);

    invert_vertex_order(vertexes);

    uint32_t j = 0;
    for (size_t i = 0; i < vertexes.size(); i += 3)
    {
        if (!check_in_bounds(vertexes[i] * scale_factor)
                || !check_in_bounds(vertexes[i+1] * scale_factor)
                || !check_in_bounds(vertexes[i+2] * scale_factor))
            continue;

        // TODO: export surfaces types to function argument
        surface_array[j].type = 0x0000; // SURFACE_DEFAULT
        surface_array[j].force = 0;
        surface_array[j].terrain = 0x0002; // TERRAIN_SNOW
        surface_array[j].vertices[0][0] = (int16_t) ( vertexes[i+0].z * scale_factor);
        surface_array[j].vertices[0][1] = (int16_t) ( vertexes[i+0].y * scale_factor);
        surface_array[j].vertices[0][2] = (int16_t) (-vertexes[i+0].x * scale_factor);
        surface_array[j].vertices[1][0] = (int16_t) ( vertexes[i+1].z * scale_factor);
        surface_array[j].vertices[1][1] = (int16_t) ( vertexes[i+1].y * scale_factor);
        surface_array[j].vertices[1][2] = (int16_t) (-vertexes[i+1].x * scale_factor);
        surface_array[j].vertices[2][0] = (int16_t) ( vertexes[i+2].z * scale_factor);
        surface_array[j].vertices[2][1] = (int16_t) ( vertexes[i+2].y * scale_factor);
        surface_array[j].vertices[2][2] = (int16_t) (-vertexes[i+2].x * scale_factor);

        j++;
    }

    surface_object.surfaces = surface_array;
    surface_object.surfaceCount = j;

    surface_object.transform.position[0] =  position.z * scale_factor;
    surface_object.transform.position[1] =  position.y * scale_factor;
    surface_object.transform.position[2] = -position.x * scale_factor;

    surface_object.transform.eulerRotation[0] = -godot::Math::rad2deg(rotation.z);
    surface_object.transform.eulerRotation[1] = -godot::Math::rad2deg(rotation.y);
    surface_object.transform.eulerRotation[2] =  godot::Math::rad2deg(rotation.x);

    id = sm64_surface_object_create(&surface_object);

    ::free(surface_array);

    return id;
}

void SM64Handler::surface_object_move(int object_id, godot::Vector3 position, godot::Vector3 rotation)
{
    struct SM64ObjectTransform transform;

    transform.position[0] =  position.z * scale_factor;
    transform.position[1] =  position.y * scale_factor;
    transform.position[2] = -position.x * scale_factor;

    transform.eulerRotation[0] = -godot::Math::rad2deg(rotation.z);
    transform.eulerRotation[1] = -godot::Math::rad2deg(rotation.y);
    transform.eulerRotation[2] =  godot::Math::rad2deg(rotation.x);

    sm64_surface_object_move(object_id, &transform);
}

void SM64Handler::surface_object_delete(int object_id)
{
    sm64_surface_object_delete(object_id);
}

void SM64Handler::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("global_init"), &SM64Handler::global_init);
    godot::ClassDB::bind_method(godot::D_METHOD("is_init"), &SM64Handler::is_init);
    godot::ClassDB::bind_method(godot::D_METHOD("get_mario_image"), &SM64Handler::get_mario_image);
    godot::ClassDB::bind_method(godot::D_METHOD("set_rom_filename", "value"), &SM64Handler::set_rom_filename);
    godot::ClassDB::bind_method(godot::D_METHOD("get_rom_filename"), &SM64Handler::get_rom_filename);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::STRING, "rom_filename", godot::PROPERTY_HINT_GLOBAL_FILE, "*.n64,*.z64,"), "set_rom_filename", "get_rom_filename");
    godot::ClassDB::bind_method(godot::D_METHOD("set_scale_factor", "value"), &SM64Handler::set_scale_factor);
    godot::ClassDB::bind_method(godot::D_METHOD("get_scale_factor"), &SM64Handler::get_scale_factor);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "scale_factor"), "set_scale_factor", "get_scale_factor");
    godot::ClassDB::bind_method(godot::D_METHOD("static_surfaces_load", "vertexes"), &SM64Handler::static_surfaces_load);
    godot::ClassDB::bind_method(godot::D_METHOD("mario_create", "position"), &SM64Handler::mario_create);
    godot::ClassDB::bind_method(godot::D_METHOD("mario_tick", "mario_id", "input"), &SM64Handler::mario_tick);
    godot::ClassDB::bind_method(godot::D_METHOD("mario_delete", "mario_id"), &SM64Handler::mario_delete);
    godot::ClassDB::bind_method(godot::D_METHOD("surface_object_create", "vertexes", "position", "rotation"), &SM64Handler::surface_object_create);
    godot::ClassDB::bind_method(godot::D_METHOD("surface_object_move", "object_id", "position", "rotation"), &SM64Handler::surface_object_move);
    godot::ClassDB::bind_method(godot::D_METHOD("surface_object_delete", "object_id"), &SM64Handler::surface_object_delete);
}
