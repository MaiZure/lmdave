#ifndef LMDAVE_H
#define LMDAVE_H

#include <SDL.h>

/* Format of the level information
 * -path is used for monster movement
 * -tiles contain tileset indices
 * -padding unused but included for capatibility
 */
struct dave_level {
	int8_t path[256];
	uint8_t tiles[1000];
	uint8_t padding[24];
};

/* Monster state information for a single monster
 * -type is the tileset number (0 is unused)
 * -path_index references dave_level path data
 * -dead_timer is used for death delay
 * - *_p[xy] contain world or waypoint data
 */
struct monster_state
{
	uint8_t type;
	uint8_t path_index;
	uint8_t dead_timer;
	uint8_t monster_x;
	uint8_t monster_y;
	uint16_t monster_px;
	uint16_t monster_py;
	int8_t next_px;
	int8_t next_py;
};


/* Game state information in kitchen-sink format
 *    (Refactor me please!!!)
 */
struct game_state {
	uint8_t quit;
	uint8_t tick;
	uint8_t dave_tick;
	uint8_t current_level;
	uint8_t lives;
	uint32_t score;
	uint8_t view_x;
	uint8_t view_y;
	int8_t dave_x;
	int8_t dave_y;
	uint8_t dave_dead_timer;
	uint16_t dbullet_px;
	uint16_t dbullet_py;
	int8_t dbullet_dir;
	uint16_t ebullet_px;
	uint16_t ebullet_py;
	int8_t ebullet_dir;
	int16_t dave_px;
	int16_t dave_py;
	uint8_t on_ground;
	int8_t scroll_x;
	int8_t last_dir;

	uint8_t dave_right;
	uint8_t dave_left;
	uint8_t dave_jump;
	uint8_t dave_fire;
	uint8_t dave_down;
	uint8_t dave_up;
	uint8_t dave_climb;
	uint8_t dave_jetpack;
	uint8_t jetpack_delay;
	uint8_t jump_timer;
	uint8_t try_right;
	uint8_t try_left;
	uint8_t try_jump;
	uint8_t try_fire;
	uint8_t try_jetpack;
	uint8_t try_down;
	uint8_t try_up;
	uint8_t check_pickup_x;
	uint8_t check_pickup_y;
	uint8_t check_door;
	uint8_t can_climb;
	uint8_t collision_point[9];
	uint8_t trophy;
	uint8_t gun;
	uint8_t jetpack;

	struct monster_state monster[5];

	struct dave_level level[10];
};


/* Game asset structure
 * Only tileset data for now
 * Could include music/sounds, etc
 */
struct game_assets {
	SDL_Texture *graphics_tiles[158];
};


/* Forward declarations */
void init_game(struct game_state *);
void init_assets(struct game_assets *, SDL_Renderer *);
void check_input(struct game_state *);
void update_game(struct game_state *);
void render(struct game_state *, SDL_Renderer *, struct game_assets *);
void check_collision(struct game_state *);
void clear_input(struct game_state *);
void pickup_item(struct game_state *, uint8_t, uint8_t);
void start_level(struct game_state *);
void update_dbullet(struct game_state *);
void update_ebullet(struct game_state *);
void verify_input(struct game_state *);
void move_dave(struct game_state *);
void move_monsters(struct game_state *);
void fire_monsters(struct game_state *);
void scroll_screen(struct game_state *);
void apply_gravity(struct game_state *);
void update_level(struct game_state *);
void restart_level(struct game_state *);
uint8_t update_frame(struct game_state *, uint8_t, uint8_t);
void draw_world(struct game_state *, struct game_assets *, SDL_Renderer *);
void draw_dave(struct game_state *, struct game_assets *, SDL_Renderer *);
void draw_dave_bullet(struct game_state *, struct game_assets *, SDL_Renderer *);
void draw_monster_bullet(struct game_state *, struct game_assets *, SDL_Renderer *);
void draw_monsters(struct game_state *, struct game_assets *, SDL_Renderer *);
void draw_ui(struct game_state *, struct game_assets *, SDL_Renderer *);

uint8_t is_clear(struct game_state *, uint16_t, uint16_t, uint8_t);
uint8_t is_visible(struct game_state *, uint16_t);
void add_score(struct game_state *, uint16_t);
#endif
