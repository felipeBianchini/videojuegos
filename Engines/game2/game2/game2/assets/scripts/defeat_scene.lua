scene = {
    sprites = {    },
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
    },
    entities = {
        [1] = {
            components = {
                sprite = {
                    assetId = "background",
                    width = 480,
                    heigth = 272,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 0.0, y = 2000.0},
                    scale = {x = 3.0, y = 3.0},
                    rotation = 0.0,
                }
            }
        }
    },
}