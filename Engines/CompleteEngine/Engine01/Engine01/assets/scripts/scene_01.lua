scene = {
    sprites = {
        [1] = {assetId = "alan", filePath = "./assets/images/enemy_alan.png"},
        [2] = {assetId = "crushingCyclops", filePath = "./assets/images/CrushingCyclops.png"}
    },

    keys = {
        [1] = {name = "up", key = 119},
        [2] = {name = "down", key = 115},
        [3] = {name = "left", key = 97},
        [4] = {name = "right", key = 100},
    },

    entities = {
        [1] = {
            components = {
                circle_collider = {
                    radius = 8,
                    width = 16,
                    heigth = 16
                },
                rigid_body = {
                    velocity = {x = 0, y = 0},
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "alan",
                    width = 16,
                    heigth = 16,
                    src_rect = {x = 16, y = 0},
                },
                transform = {
                    position = {x = 400.0, y = 300.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                }
            }
        }
    },
}