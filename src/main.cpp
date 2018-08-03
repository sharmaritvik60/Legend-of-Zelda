#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "boat.h"
#include "rock.h"
#include "health.h"
#include "monster.h"
#include "barrel.h"
#include "boss.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
Boss boss;

/**************************
* Customizable functions *
**************************/
int window_width = 1024;
int window_height = 768;
Sea sea;
Boat boat;
Rock rock[100];
int boat_view = 0, follow_view = 1, top_view = 0, flag_barrel=0, last_time=-1, monster_ball_count=0, last_ball_time=-1, health_count=0;
int alive_rock[100];
int alive_health[100], is_fast = 0;
int alive_barrel[100];
int alive_monster[100];
int alive_monster_balls[1000], alive_ball[1000];
int wind_time = 0, camera_number=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, shoot_x=-1000.0f, shoot_y=-1000.0f, shoot_z=-1000.0f;
float camera_rotation_angle = 90.0f;
int dir = -1, player_health = 100, player_points=0;
float cursor_x=-1.0f, cursor_y=-1.0f, helicopter_x=-1000.0f, helicopter_y=-1000.0f, helicopter_z=-1000.0f, eye_x, eye_y, eye_z;
Health health[100];
int boss_dir=-1, monsters_left=6;
Ball monster_ball[1000], ball[1000];
Monster monster[100];
int monster_dir[100];
Barrel barrel[100];
int dir_barrel[100], boss_alive=0, pressed=0, shoot_mode=0, ball_count;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void cursor_pressed()
{
    pressed = 1;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    cursor_x = x;
    cursor_y = y;
    if(camera_number == 4)
    {
        if(helicopter_x==-1000.0f && helicopter_y==-1000.0f && helicopter_z==-1000.0f)
        {
            helicopter_x = boat.position.x;
            helicopter_y = 1.0f;
            helicopter_z = boat.position.z;
        }
    }
    return;
}

void zoom(float yoffset)
{
    if((camera_number!=4) || shoot_mode)
        return;
    eye_x += (yoffset*0.1f*(helicopter_x-eye_x)/sqrt((helicopter_x-eye_x)*(helicopter_x-eye_x) + (helicopter_y-eye_y)*(helicopter_y-eye_y) + (helicopter_z-eye_z)*(helicopter_z-eye_z)));
    eye_y += (yoffset*0.1f*(helicopter_y-eye_y)/sqrt((helicopter_x-eye_x)*(helicopter_x-eye_x) + (helicopter_y-eye_y)*(helicopter_y-eye_y) + (helicopter_z-eye_z)*(helicopter_z-eye_z)));
    eye_z += (yoffset*0.1f*(helicopter_z-eye_z)/sqrt((helicopter_x-eye_x)*(helicopter_x-eye_x) + (helicopter_y-eye_y)*(helicopter_y-eye_y) + (helicopter_z-eye_z)*(helicopter_z-eye_z)));
    return;
}

void cursor_released()
{
    pressed = 0;
    camera_rotation_angle = 90.0f;
    return;
}

void enter_shooting_mode()
{
    shoot_mode = 1;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    cursor_x = x;
    cursor_y = y;
    shoot_x = boat.position.x;
    shoot_y = 1.0f;
    shoot_z = boat.position.z;
    return;
}

void exit_shooting_mode()
{
    shoot_mode = 0;
    camera_rotation_angle = 90.0f;
    return;
}

void detect_collision_rock()
{
	for(int i=0;i<100;i++)
	{
		if(!alive_rock[i])
			continue;
		if(abs(rock[i].position.x-boat.position.x)<=0.55f && abs(rock[i].position.y-boat.position.y)<=0.5f && abs(rock[i].position.z-boat.position.z)<=0.7f)
		{
			alive_rock[i] = 0;
			player_health -= 10;
			if(player_health <= 0)
			{
				cout<<"Game over!!!!\n";
                cout<<"You scored "<<player_points<<" points\n";
				exit(0);
			}
		}
	}
	return;
}

void detect_collision_health()
{
	for(int i=0;i<100;i++)
	{
		if(!alive_health[i])
			continue;
		if(abs(health[i].position.x-boat.position.x)<=0.45f && abs(health[i].position.y-boat.position.y)<=0.4f && abs(health[i].position.z-boat.position.z)<=1.1f)
		{
			alive_health[i] = 0;
            if(health[i].health)
            {
    			player_health += 50;
    			if(player_health > 100)
    				player_health = 100;
            }
            else
                is_fast = 1;
		}
	}
	return;
}

void detect_collision_barrel()
{
    for(int i=0;i<100;i++)
    {
        if(!alive_barrel[i])
            continue;
        if(abs(barrel[i].position.x-boat.position.x)<=0.95f && abs(barrel[i].position.y-boat.position.y)<=0.4f && abs(barrel[i].position.z-boat.position.z)<=0.6f)
            flag_barrel = 1;
    }
}

void detect_collision_monster()
{
    if(!monsters_left)
        return;
	for(int i=0;i<100;i++)
	{
		if(!alive_monster[i])
			continue;
		if(abs(monster[i].position.x-boat.position.x)<=0.65f && abs(monster[i].position.y-boat.position.y)<=0.6f && abs(monster[i].position.z-boat.position.z)<=0.8f)
		{
			alive_monster[i] = 0;
            monsters_left--;
			player_health -= 30;
            if(!monsters_left)
                boss_alive = 1;
			if(player_health <= 0)
			{
                cout<<"Game over!!!!\n";
                cout<<"You scored "<<player_points<<" points\n";
                exit(0);
			}
		}
	}
	return;
}

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    glm::vec3 eye, target, up;
    if(shoot_mode)
    {
        eye = glm::vec3(boat.position.x-1.0f*sin(boat.rotation * M_PI/180.0f), 1.8f, boat.position.z-1.4f*cos(boat.rotation * M_PI/180.0f));
        target = glm::vec3(shoot_x, shoot_y, shoot_z);
        up = glm::vec3(0, 1, 0);
    }
    else if(camera_number == 0)
    {
    	eye = glm::vec3(boat.position.x-1.0f*sin(boat.rotation * M_PI/180.0f), 1.8f, boat.position.z-1.4f*cos(boat.rotation * M_PI/180.0f));
	    target = glm::vec3(boat.position.x, 1.0f, boat.position.z);
	    up = glm::vec3(0, 1, 0);
	}
	else if(camera_number == 1)
    {
    	eye = glm::vec3(boat.position.x+1.0*sin(boat.rotation * M_PI/180.0f), 0.8f+boat.position.y, boat.position.z+1.0f*cos(boat.rotation * M_PI/180.0f));
	    target = glm::vec3(boat.position.x+1.5f*sin(boat.rotation * M_PI/180.0f), 1.0f, boat.position.z+1.5f*cos(boat.rotation * M_PI/180.0f));
	    up = glm::vec3(0, 1, 0);
	}
	else if(camera_number == 2)
	{
		eye = glm::vec3(boat.position.x, 4.0f, boat.position.z);
	    target = glm::vec3(boat.position.x, 0.0f, boat.position.z+1.0f);
	    up = glm::vec3(0, 1, 0);
	}
    else if(camera_number == 3)
    {
        eye = glm::vec3(10, 10, 10);
        target = glm::vec3(boat.position.x, 0.0f, boat.position.z+1.0f);
        up = glm::vec3(0, 1, 0);
    }
    else if(camera_number == 4)
    {
        eye = glm::vec3(eye_x, eye_y, eye_z);
        target = glm::vec3(helicopter_x, helicopter_y, helicopter_z);
        up = glm::vec3(0, 1, 0);
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    if(boss_alive)
        boss.draw(VP);
    for(int i=0;i<100;i++)
    {
    	if(alive_monster[i])
    		monster[i].draw(VP);
    }
    for(int i=0;i<100;i++)
    {
    	if(alive_rock[i])
    		rock[i].draw(VP);
    }
    for(int i=0;i<100;i++)
    {
    	if(alive_health[i])
    		health[i].draw(VP);
    }
    for(int i=0;i<100;i++)
    {
        if(alive_barrel[i])
            barrel[i].draw(VP);
    }
    for(int i=0;i<1000;i++)
    {
        if(alive_monster_balls[i] && boss_alive)
            monster_ball[i].draw(VP);
    }
    for(int i=0;i<1000;i++)
    {
        if(alive_ball[i])
            ball[i].draw(VP);
    }
    boat.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int cam = glfwGetKey(window, GLFW_KEY_C);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);
    if (left) {
    	boat.rotation += (1+is_fast);
        // Do something
    }
    if (right) {
    	boat.rotation -= (1+is_fast);
        // Do something
    }
    if (up) {
    	boat.position.z += ((0.05f+0.05f*is_fast)*cos(M_PI*boat.rotation/180.0f));
    	boat.position.x += ((0.05f+0.05f*is_fast)*sin(M_PI*boat.rotation/180.0f));
        // Do something
    }
    if (down) {
    	boat.position.z -= ((0.05f+0.05f*is_fast)*cos(M_PI*boat.rotation/180.0f));
    	boat.position.x -= ((0.05f+0.05f*is_fast)*sin(M_PI*boat.rotation/180.0f));
        // Do something
    }
    flag_barrel = 0;
    detect_collision_barrel();
    if(flag_barrel)
    {
        if (left) {
        boat.rotation -= 1;
        // Do something
        }
        if (right) {
            boat.rotation += 1;
            // Do something
        }
        if (up) {
            boat.position.z -= (0.05f*cos(M_PI*boat.rotation/180.0f));
            boat.position.x -= (0.05f*sin(M_PI*boat.rotation/180.0f));
            // Do something
        }
        if (down) {
            boat.position.z += (0.05f*cos(M_PI*boat.rotation/180.0f));
            boat.position.x += (0.05f*sin(M_PI*boat.rotation/180.0f));
            // Do something
        }
    }
    if(jump && boat.position.y<=0.05f)
        boat.speed.y = 0.13f;
    if(cam && (wind_time-last_time)>=30)
    {
        camera_number = (camera_number+1)%5;
        helicopter_x = boat.position.x;
        helicopter_y = 1;
        helicopter_z = boat.position.z;
        last_time = wind_time;
        eye_x = boat.position.x-sin(boat.rotation * M_PI/180.0f);
        eye_y = 1.8f;
        eye_z = boat.position.z-1.4f*cos(boat.rotation * M_PI/180.0f);
    }
    if(f && shoot_mode && (wind_time-last_ball_time)>=30)
    {
        float ang = camera_rotation_angle;
        float ang1 = shoot_y;
        ball[ball_count] = Ball(boat.position.x, 1.0f, boat.position.z, COLOR_ORANGE, ang, ang1);
        alive_ball[ball_count] = 1;
        ball_count++;
        last_ball_time = wind_time;
    }
    return;
}

void tick_wind()
{
	wind_time++;
	if(wind_time%1200 == 0)
	{
		if((wind_time/1200)%4 == 0)
		{
			boat.wind_rotation = 15;	
			boat.speed.x = -0.01f;
		}
		if((wind_time/1200)%4 == 1)
		{
			boat.wind_rotation = 0;
			boat.speed.x = 0.0f;
		}
		if((wind_time/1200)%4 == 2)
		{
			boat.wind_rotation = -15;
			boat.speed.x = 0.01f;
		}
		if((wind_time/1200)%4 == 3)
		{
			boat.wind_rotation = 0;
			boat.speed.x = 0.0f;
		}
	}
	return;
}

void tick_monster()
{
	for(int i=0;i<100;i++)
	{
		if(!alive_monster[i])
			continue;
		if(monster_dir[i] == -1)
		{
			monster[i].position.x -= 0.01f;
			if(monster[i].position.x <= -10)
				monster_dir[i] = 1;
		}
		else
		{
			monster[i].position.x += 0.01f;
			if(monster[i].position.x >= 10)
				monster_dir[i] = -1;
		}
	}
    if(boss_alive)
    {
        if(wind_time%300 == 0)
        {
            monster_ball[monster_ball_count] = Ball(boss.position.x, 0.8f, boss.position.z, COLOR_YELLOW, 0.0f, 0.0f);
            alive_monster_balls[monster_ball_count] = 1;
            monster_ball_count++;
        }
        if(boss_dir == -1)
        {
            boss.position.x -= 0.05f;
            if(boss.position.x <= -8)
                boss_dir = 1;
        }
        else
        {
            boss.position.x += 0.05f;
            if(boss.position.x >= 8)
                boss_dir = -1;
        }
        for(int i=0;i<monster_ball_count;i++)
            monster_ball[i].position.z -= 0.08f;
    }
	return;
}

void tick_barrel()
{
    for(int i=0;i<100;i++)
    {
        if(dir_barrel[i] == -1)
        {
        	barrel[i].position.y -= 0.005f;
        	if(barrel[i].position.y <= -0.07f)
        		dir_barrel[i] = 1;
        }
        else
        {
        	barrel[i].position.y += 0.005f;
        	if(barrel[i].position.y >= 0.07f)
        		dir_barrel[i] = -1;
        }
    }
	return;
}

void detect_collision_powerup()
{
    for(int i=0;i<100;i++)
    {
        if(!alive_barrel[i])
            continue;
        if(!barrel[i].powerup_present)
            continue;
        if(abs(barrel[i].position.x-boat.position.x)<=0.45f && abs(1.05f-boat.position.y)<=0.4f && abs(barrel[i].position.z-boat.position.z)<=0.6f)
        {
            barrel[i].powerup_present = 0;
            player_points += barrel[i].points;
        }
    }
    return;
}

void tick_camera(int flg)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if(flg)
    {
        helicopter_y = (y-cursor_y)*0.005f;
        camera_rotation_angle = 90.0f+(x-cursor_x)*0.005f;
        helicopter_x = boat.position.x+cos(camera_rotation_angle);
        helicopter_z = boat.position.z+sin(camera_rotation_angle);
        return;
    }
    shoot_y = (y-cursor_y)*0.001f;
    camera_rotation_angle = 90.0f+(x-cursor_x)*0.001f;
    shoot_x = boat.position.x+cos(camera_rotation_angle);
    shoot_z = boat.position.z+sin(camera_rotation_angle);
    return;
}

void detect_collision_monster_ball()
{
    if(!alive_monster)
        return;
    for(int i=0;i<1000;i++)
    {
        if(!alive_monster_balls[i])
            continue;
        if(abs(monster_ball[i].position.x-boat.position.x)<=0.45f && abs(monster_ball[i].position.z-boat.position.z)<=0.6f)
        {
            alive_monster_balls[i] = 0;
            player_health -= 30;
            if(player_health <= 0)
            {
                cout<<"You lost\n";
                exit(0);
            }
        }
    }
    return;
}

void tick_ball()
{
    for(int i=0;i<1000;i++)
    {
        if(!alive_ball[i])
            continue;
        ball[i].position.x += (0.4f*cos(ball[i].angle));
        ball[i].position.z += (0.4f*sin(ball[i].angle));
        ball[i].speed.y -= 0.002f;
        ball[i].position.y += ball[i].speed.y;
        if(ball[i].position.y <= 0)
            alive_ball[i] = 0;
    }
    return;
}

void detect_collision_ball()
{
    for(int i=0;i<1000;i++)
    {
        if(!alive_ball[i])
            continue;
        if(boss_alive && abs(boss.position.x-ball[i].position.x)<=0.9f && abs(boss.position.y-ball[i].position.y)<=1.0f && abs(boss.position.z-ball[i].position.z)<=0.9f)
        {
            boss.health -= 25;
            if(boss.health <= 0)
            {
                boss_alive = 0;
                health[health_count] = Health(boss.position.x, 0.2f, boss.position.z, COLOR_RED, 0);
                alive_health[health_count] = 1;
                health_count++;
            }
            alive_ball[i] = 0;
        }
        else
        {
            for(int j=0;j<100;j++)
            {
                if(alive_monster[j] && abs(monster[j].position.x-ball[i].position.x)<=0.6f && abs(monster[j].position.y-ball[i].position.y)<=0.6f && abs(monster[j].position.z-ball[i].position.z)<=0.6f)
                {
                    alive_monster[j] = 0;
                    alive_ball[i] = 0;
                    health[health_count] = Health(monster[j].position.x, 0.2f, monster[j].position.z, COLOR_GREEN, 1);
                    alive_health[health_count] = 1;
                    health_count++;
                    monsters_left--;
                    if(!monsters_left)
                        boss_alive = 1;
                    break;
                }
            }
        }
    }
    return;
}

void tick_elements() {
    boat.position.x += boat.speed.x;
    if(dir == -1)
    {
    	boat.position.y -= 0.005f;
    	if(boat.position.y <= -0.05f)
    		dir = 1;
    }
    else
    {
    	boat.position.y += 0.005f;
    	if(boat.position.y >= 0.05f)
    		dir = -1;
    }
    detect_collision_rock();
    detect_collision_health();
    detect_collision_monster();
    detect_collision_powerup();
    detect_collision_monster_ball();
    detect_collision_ball();
    tick_monster();
    tick_wind();
    tick_barrel();
    tick_ball();
    for(int i=0;i<100;i++)
    {
    	if(alive_health[i])
    		health[i].rotation += 1;
    }
    boat.speed.y -= 0.005f;
    if(boat.speed.y<0 && boat.position.y<=0.05f)
        boat.speed.y = 0;
    boat.position.y += boat.speed.y;
    if(camera_number==4 && pressed)
        tick_camera(1);
    else if(shoot_mode)
        tick_camera(0);
    if(camera_number==4 && !pressed)
    {
        helicopter_x = boat.position.x;
        helicopter_y = 1.0f;
        helicopter_z = boat.position.z;
    }
    return;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    for(int i=0;i<1000;i++)
    {
        alive_monster_balls[i] = 0;
        alive_ball[i] = 0;
    }
    sea = Sea(0, 0, 0, COLOR_SEA);
    boat = Boat(0, 0, 0, COLOR_RED);
    rock[0] = Rock(1, 0, 1, COLOR_BLACK);
    rock[1] = Rock(8, 0, 4, COLOR_BLACK);
    rock[2] = Rock(4, 0, 4, COLOR_BLACK);
    rock[3] = Rock(-4, 0, 4, COLOR_BLACK);
    rock[4] = Rock(2, 0, -5, COLOR_BLACK);
    rock[5] = Rock(-5, 0, 3, COLOR_BLACK);
    for(int i=0;i<6;i++)
    	alive_rock[i] = 1;
    monster[0] = Monster(0, 0.6f, 3, COLOR_MONSTER);
    monster[1] = Monster(0, 0.6f, 6, COLOR_MONSTER);
    monster[2] = Monster(0, 0.6f, 11, COLOR_MONSTER);
    monster[3] = Monster(0, 0.6f, 17, COLOR_MONSTER);
    monster[4] = Monster(0, 0.6f, 21, COLOR_MONSTER);
    monster[5] = Monster(0, 0.6f, -3, COLOR_MONSTER);
    for(int i=0;i<6;i++)
    	alive_monster[i] = 1;
    // Create and compile our GLSL program from the shaders
    for(int i=0;i<100;i++)
    {
        if(i%2)
            dir_barrel[i] = -1;
        else
            dir_barrel[i] = 1;
    }
    boss = Boss(15, 2, 15, COLOR_BOSS);
    boss_alive = 0;
    barrel[0] = Barrel(10, 0, 10, COLOR_BROWN);
    barrel[1] = Barrel(12, 0, 15, COLOR_BROWN);
    barrel[2] = Barrel(-2, 0, 8, COLOR_BROWN);
    barrel[3] = Barrel(15, 0, 20, COLOR_BROWN);
    barrel[4] = Barrel(18, 0, 11, COLOR_BROWN);
    barrel[5] = Barrel(2, 0, 28, COLOR_BROWN);
    for(int i=0;i<6;i++)
        alive_barrel[i] = 1;
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    for(int i=0;i<100;i++)
    {
    	if(i%2)
    		monster_dir[i] = -1;
    	else
    		monster_dir[i] = 1;
    }

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    audio_init();
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        audio_play();
        if (t60.processTick()) {
            stringstream ss, title, m_health;
            string str, str1;
            ss << player_health;
            str1 = ss.str();
            str = "Player health: ";
            str.append(str1);
            str1 = " | Score: ";
            str.append(str1);
            title << player_points;
            str1 = title.str();
            str.append(str1);
            if(alive_monster)
            {
                str1 = " | Boss health: ";
                str.append(str1);
                m_health << boss.health;
                str1 = m_health.str();
                str.append(str1);
            }
            const char *final = str.c_str();
            glfwSetWindowTitle(window, final);
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float near = 0.0f;
    float far = 800.0f;
    GLfloat fov = 150.0f/1.3f;
    Matrices.projection = glm::perspective(fov, (GLfloat) window_width / (GLfloat) window_height, near, far);
}
