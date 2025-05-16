#include "Rectangle2D.h"
#include "Missile.h"
#include "Random.h"
#include <raylib.h>
#include <raymath.h>
#include <forward_list> // for std::forward_list()
#include <optional>     // for std::optional
#include <cassert>      // for assert

void updateMissiles(std::forward_list<Missile> &missiles);

void setupPlayerMissile(Missile &playerMissile);
void setupEnemyMissile(Missile &enemyMissile);

void setupBigBuildings(std::forward_list<Rectangle2D> &buildings);
void setupSmallBuildings(std::forward_list<Rectangle2D> &buildings);

void placeBuildings(std::forward_list<Rectangle2D> &buildings, int noOfBuildings, float buildingW, float buildingH, const Color &color, float width, float innerPadding, float outerPadding);

std::optional<float> getTallestBuilding(const std::forward_list<Rectangle2D> &buildings);

void applyCollisions(std::forward_list<Missile> &missiles, std::forward_list<Rectangle2D> &buildings, float buildingCollisionThreshold);

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "Missile Commander");

    SetTargetFPS(60);

    /*
    I'm wondering that I can extend Line2D
    and add a property like missile distance.
    And it will keep my codebase modular
    and in future I can easily use Line2D class
    as it is. However, it might add a little bit
    of complexcity in my code.
    */

    // a list that will store all the shot missiles
    // it's a singly-linked list so iteration
    // will only happen from the front of the list.
    std::forward_list<Missile> missiles{};

    // a list that will store all the buildings
    // it's a singly-linked list so iteration
    // will only happen from the front of the list.
    std::forward_list<Rectangle2D> buildings{};

    // setup all the buildings based on their
    // pre-defined constants and store it
    // in the building list
    setupBigBuildings(buildings);

    setupSmallBuildings(buildings);

    // this object is a class type (std::optional)
    // so make sure before it's non-null
    // before using it
    // also make sure that you call getTallestBuilding()
    // on a non-empty list
    const std::optional<float> tallestBuilding{getTallestBuilding(buildings)};

    assert(tallestBuilding && "Something went wrong here!");

    // this will help us when to start detecting
    // for collision with all buildings
    const float buildingCollisionThreshold{screenH - *tallestBuilding};

    while (!WindowShouldClose())
    {
        // detect if user had clicked on the screen
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // if so, create a new player missile
            Missile playerMissile{};

            setupPlayerMissile(playerMissile);

            // add the newly created missile
            // at the front of the list
            missiles.push_front(playerMissile);
        }

        static int s_frameCounter{};

        // assuming FPS is set to 60 then
        // 60 frames: one second
        // 120 frames: two second
        // ...
        constexpr int secondsInFrames{60};

        // after certain seconds generate
        // enemy's missile
        if (++s_frameCounter == secondsInFrames)
        {
            Missile enemyMissile{};

            setupEnemyMissile(enemyMissile);

            // add the newly created missile
            // at the front of the list
            missiles.push_front(enemyMissile);

            // rest the frame counter
            s_frameCounter = 0;
        }

        // UPDATE ALL MISSILES
        updateMissiles(missiles);

        applyCollisions(missiles, buildings, buildingCollisionThreshold);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DRAW ALL MISSILES
        for (const Missile &missile : missiles)
        {
            DrawLineV(missile.getStartPos(), missile.getEndPos(), missile.getTint());
            DrawCircleV(missile.getEndPos(), 5.0f, RED);
        }

        // DRAW ALL BUILDINGS
        for (const Rectangle2D &building : buildings)
            DrawRectangleRec(building.getRectangle(), building.getTint());

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void updateMissiles(std::forward_list<Missile> &missiles)
{

    // return back to caller if missiles list is empty
    if (missiles.empty())
        return;

    for (auto missile{missiles.begin()}; missile != missiles.cend(); ++missile)
    {
        // now, shoot a new missile towards its target position
        // based on certain distance
        // after every frame, increment the end position of missile
        missile->setEndPos(Vector2MoveTowards(missile->getEndPos(), missile->getTargetPos(), missile->getMissileDistance()));

        // increase missile's distance by its respective speed
        missile->updateMissileDistance(missile->getMissileSpeed());

        // these numbers are set using trial-and-error
        constexpr float minDistance{0.0f};
        constexpr float maxDistance{100.0f};

        // clamp missile's distance
        // so that the value does'nt overflow
        missile->setMissileDistance(Clamp(missile->getMissileDistance(), minDistance, maxDistance));
    }
}

void setupPlayerMissile(Missile &playerMissile)
{

    // initialise the new missile
    // set a fixed position from where the player
    // will shoot their missiles
    playerMissile.setStartPos(Vector2{
        static_cast<float>(GetScreenWidth()) / 2.0f,
        static_cast<float>(GetScreenHeight()) / 2.0f,
    });

    // and set player's missile end position to starting position
    playerMissile.setEndPos(playerMissile.getStartPos());

    // set player's missile distance
    // missile's distance is zero by default

    // these numbers are set using trial-and-error
    constexpr float playerMissileSpeed{1.0f};

    // set the speed of player's missile
    playerMissile.setMissileSpeed(playerMissileSpeed);

    // set missile's color
    playerMissile.setTint(GREEN);

    // now, set the clicked position as target position
    playerMissile.setTargetPos(GetMousePosition());
}

void setupEnemyMissile(Missile &enemyMissile)
{
    // set a random starting position of the missile
    // all starting position's Y should be zero
    enemyMissile.setStartPos(Vector2{
        static_cast<float>(Random::get(0, GetScreenWidth())),
        0,
    });

    // set the end position of the missile same
    // as starting position
    enemyMissile.setEndPos(enemyMissile.getStartPos());

    // set enemy's missile distance
    // missile's distance is zero by default

    // these numbers are set using trial-and-error
    constexpr float enemyMissileSpeed{0.01f};

    // set the speed of enemy's missile
    enemyMissile.setMissileSpeed(enemyMissileSpeed);

    // set missile's color
    // default value is RED

    // now, set a random position as target position
    // all target position's Y should be equivalent to screen height
    enemyMissile.setTargetPos(Vector2{
        static_cast<float>(Random::get(0, GetScreenWidth())),
        static_cast<float>(GetScreenHeight()),
    });
}

void placeBuildings(std::forward_list<Rectangle2D> &buildings, int noOfBuildings, float buildingW, float buildingH, const Color &color, float width, float innerPadding, float outerPadding)
{
    for (float i{0}; i < static_cast<float>(noOfBuildings); ++i)
    {
        // set building's width and height respectively
        Rectangle2D building{buildingW, buildingH};

        // because we want to show the last building inside the width
        const float newWidth{width - building.getWidth()};

        // calculated gap between each building using new width
        const float gap{newWidth / static_cast<float>(noOfBuildings)};

        // to keep a symmetry and consistency
        // innerPadding + outerPadding = (gap / 2)

        building.setPosition(Vector2{
            (gap + innerPadding) * i + outerPadding,
            static_cast<float>(GetScreenHeight()) - building.getHeight(),
        });

        building.setTint(color);

        buildings.push_front(building);
    }
}

void setupBigBuildings(std::forward_list<Rectangle2D> &buildings)
{
    constexpr float bigBuildingW{80.0f};
    constexpr float bigBuildingH{80.0f};
    constexpr Color bigBuildingColor{GRAY};

    // constants related to big buildings
    constexpr float maxBigBuildings{3.0f};
    constexpr float innerPadding{100.0f};
    constexpr float outerPadding{20.0f};

    placeBuildings(buildings, maxBigBuildings, bigBuildingW, bigBuildingH,
                   bigBuildingColor, static_cast<float>(GetScreenWidth()), innerPadding, outerPadding);
}

void setupSmallBuildings(std::forward_list<Rectangle2D> &buildings)
{
    constexpr float smallBuildingW{40.0f};
    constexpr float smallBuildingH{40.0f};
    constexpr Color smallBuildingColor{LIGHTGRAY};

    // constants related to small buildings
    constexpr float maxSmallBuildings{3.0f};
    constexpr float innerPadding{0.0f};
    constexpr float outerPadding{145.0f};
    constexpr float bigBuildingGap{240.0f};

    // place one set of small buildings on left side
    placeBuildings(buildings, maxSmallBuildings,
                   smallBuildingW, smallBuildingH,
                   smallBuildingColor, bigBuildingGap,
                   innerPadding, outerPadding);

    // place one set of small buildings on right side
    placeBuildings(buildings, maxSmallBuildings,
                   smallBuildingW, smallBuildingH,
                   smallBuildingColor, bigBuildingGap,
                   innerPadding,

                   // move this set of buildings to right side
                   // this below multiplication is based on trial-and-error
                   outerPadding * 3.35f);
}

std::optional<float> getTallestBuilding(const std::forward_list<Rectangle2D> &buildings)
{
    // return null if building list is empty
    if (buildings.empty())
        return std::nullopt;

    float tallestBuilding{};

    for (const Rectangle2D &building : buildings)
    {
        if (tallestBuilding < building.getHeight())
            tallestBuilding = building.getHeight();
    }

    return tallestBuilding;
}

void applyCollisions(std::forward_list<Missile> &missiles, std::forward_list<Rectangle2D> &buildings, float buildingCollisionThreshold)
{
    // return if any of the list is empty
    // simply return
    if (missiles.empty() || buildings.empty())
        return;

    // used to keep track of previous missile
    // this iterator should always be initialised
    // with an iterator pointing before the first iterator
    auto previousMissile{missiles.before_begin()};

    for (auto missile{missiles.begin()}; missile != missiles.cend(); ++missile)
    {
        // if the missile reaches its target position
        // remove it from the list

        // Vector2Equals return int
        // zero means false
        // non-zero means true
        if (Vector2Equals(missile->getEndPos(), missile->getTargetPos()))
        {
            // erase_after(itr) returns
            // an iterator pointing to the element following
            // the one that was erased, or
            // end() if no such element exists.
            missile = missiles.erase_after(previousMissile);

            // return back to caller once we reach
            // the end of the list
            if (missile == missiles.cend())
                return;
        }
        else if (buildingCollisionThreshold < missile->getEndPos().y)
        {
            // used to keep track of previous missile
            // this iterator should always be initialised
            // with an iterator pointing before the first iterator
            auto previousBuilding{buildings.before_begin()};

            for (auto building{buildings.begin()}; building != buildings.cend(); ++building)
            {

                // check if the missile's color is equal to
                // enemy's missile's color
                if (ColorIsEqual(missile->getTint(), RED))
                {
                    // if so, then check for collision with buildings
                    if (CheckCollisionPointRec(missile->getEndPos(), building->getRectangle()))
                    {
                        // erase_after(itr) returns
                        // an iterator pointing to the element following
                        // the one that was erased, or
                        // end() if no such element exists.
                        missile = missiles.erase_after(previousMissile);

                        // remove the collided building from the list
                        building = buildings.erase_after(previousBuilding);

                        // return back to caller once we reach
                        // the end of the list
                        if (missile == missiles.cend())
                            return;

                        if (building == buildings.cend())
                            return;
                    }
                }

                // increment the iterator to point to next iterator
                // on the list
                ++previousBuilding;
            }
        }

        // increment the iterator to point to next iterator
        // on the list
        ++previousMissile;
    }
}