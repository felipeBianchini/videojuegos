scene = {
    sprites = {
        [1] = {assetId = "frog_idle", filePath = "./assets/images/frog_idle.png"},
        [2] = {assetId = "terrain", filePath = "./assets/images/terrain.png"},
    },
    fonts = {},
    keys = {
        [1] = {name = "up", key = 119},
        [2] = {name = "down", key = 115},
        [3] = {name = "left", key = 97},
        [4] = {name = "right", key = 100},
    },
    buttons = {},
    maps = {
        map_path = "./assets/map/level_01.tmx",
        tile_path = "./assets/map/terrain.tsx",
        tile_name = "terrain"
    },
    entities = {
        [1] = {
            components = {
                camera_follow = {},
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
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
                }
            }
        },
    },
}