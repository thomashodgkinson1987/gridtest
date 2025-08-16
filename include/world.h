#ifndef WORLD_H
#define WORLD_H

#include "actor.h"
#include "actor_array.h"
#include "tile_map.h"
#include "tile_prototype_repository.h"

/**
 * @brief Encapsulates all game world data, including the tile map and actors.
 *
 * This struct acts as a container for the game level's state, abstracting
 * away the direct management of the tile map and actor array from the
 * main game logic.
 */
typedef struct World
{
    TileMap *tile_map;
    ActorArray *actors;
} World;

/**
 * @brief Creates and initializes a new World object.
 *
 * Allocates memory for the World struct and its internal TileMap and
 * ActorArray. The tile map is initialized based on the provided dimensions
 * and a tile prototype repository.
 *
 * @param width The width of the world's tile map.
 * @param height The height of the world's tile map.
 * @param tile_prototype_repository A repository of tile prototypes to populate the map.
 * @return A pointer to the newly created World, or NULL on failure.
 */
World *world_create(
    int width,
    int height,
    TilePrototypeRepository *tile_prototype_repository);

/**
 * @brief Frees all memory associated with the World object.
 *
 * This function deallocates the World struct, its TileMap, and its ActorArray,
 * including all actors within the array.
 *
 * @param world A pointer to the World object to be freed.
 */
void world_free(
    World *world);

/**
 * @brief Adds an actor to the world.
 *
 * @param world A pointer to the World object.
 * @param actor A pointer to the Actor to be added.
 */
void world_add_actor(
    World *world,
    Actor *actor);

/**
 * @brief Moves an actor by a given delta, handling collision detection.
 *
 * This function attempts to move the actor to the new position (x + dx, y + dy).
 * It will check the destination tile for walkability before updating the
 * actor's position.
 *
 * @param world A pointer to the World object.
 * @param actor A pointer to the Actor to move.
 * @param dx The change in the x-coordinate.
 * @param dy The change in the y-coordinate.
 * @return true if the actor moved successfully, false otherwise.
 */
bool world_move_actor(
    World *world,
    Actor *actor,
    int dx,
    int dy);

/**
 * @brief Retrieves the tile at a specific coordinate.
 *
 * @param world A pointer to the World object.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @return A pointer to the Tile at the given coordinates, or NULL if out of bounds.
 */
Tile *world_get_tile(
    World *world,
    int x,
    int y);

/**
 * @brief Retrieves the actor at a specific coordinate.
 *
 * This function is useful for checking if a tile is occupied.
 *
 * @param world A pointer to the World object.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return A pointer to the Actor at the given coordinates, or NULL if no actor is present.
 */
Actor *world_get_actor_at(
    World *world,
    int x,
    int y);

#endif // WORLD_H