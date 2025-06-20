scene = {
    sprites = {
        [1] = {assetId = "frog_idle", filePath = "./assets/images/frog_idle.png"},
        [2] = {assetId = "frog_run", filePath = "./assets/images/frog_run.png"},
        [3] = {assetId = "frog_jump", filePath = "./assets/images/frog_jump.png"},
        [4] = {assetId = "frog_fall", filePath = "./assets/images/frog_fall.png"},
        [5] = {assetId = "terrain", filePath = "./assets/images/terrain.png"},
    },
    animations = {
        [1] = {animation_id = "player_frog_idle", texture_id = "frog_idle", w = 32, h = 32, num_frames = 11, speed_rate = 15, is_loop = true},
        [2] = {animation_id = "player_frog_run", texture_id = "frog_run", w = 32, h = 32, num_frames = 12, speed_rate = 15, is_loop = true},
        [3] = {animation_id = "player_frog_jump", texture_id = "frog_jump", w = 32, h = 32, num_frames = 1, speed_rate = 1, is_loop = true},
        [4] = {animation_id = "player_frog_fall", texture_id = "frog_fall", w = 32, h = 32, num_frames = 1, speed_rate = 1, is_loop = true},
    },
    fonts = {},
    keys = {
        [1] = {name = "up", key = 119},
        [2] = {name = "down", key = 115},
        [3] = {name = "left", key = 97},
        [4] = {name = "right", key = 100},
        [5] = {name = "jump", key = 32},
    },
    buttons = {},
    maps = {
        map_path = "./assets/maps/map01/level_01.tmx",
        tile_path = "./assets/maps/map01/terrain.tsx",
        tile_name = "terrain"
    },
    entities = {
        [1] = {
            components = {
                animation = {
                    num_frames = 11,
                    speed_rate = 15,
                    is_loop = true,
                },
                camera_follow = {},
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/player_frog.lua"
                },
                sprite = {
                    assetId = "frog_idle",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 400.0, y = 300.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "player",
                }
            }
        },
    },
}