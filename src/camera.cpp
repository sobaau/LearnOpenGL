#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
Camera::Camera(glm::vec3 position) noexcept : Position(position),
                                     Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                     Up(glm::vec3(0, 0, 0)),
                                     Right(glm::vec3(0, 0, 0)),
                                     WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
                                     Yaw(YAW),
                                     Pitch(PITCH),
                                     MovementSpeed(SPEED),
                                     MouseSensitivity(SENSITIVITY),
                                     Zoom(ZOOM) 
{

    update_camera_vectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX,
               float upY, float upZ, float yaw, float pitch) : Position(glm::vec3(posX, posY, posZ)),
                                                               Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                               Up(glm::vec3(0, 0, 0)),
                                                               Right(glm::vec3(0, 0, 0)),
                                                               WorldUp(glm::vec3(upX, upY, upZ)),
                                                               Yaw(yaw),
                                                               Pitch(pitch), MovementSpeed(SPEED),
                                                               MouseSensitivity(SENSITIVITY),
                                                               Zoom(ZOOM)
{
    update_camera_vectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::process_keyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD){
        Position += Front * velocity;
    }
    if (direction == BACKWARD){
        Position -= Front * velocity;
    }
    if (direction == LEFT){
        Position -= Right * velocity;
    }
    if (direction == RIGHT){
        Position += Right * velocity;
    }
    if (direction == UP){
        Position += Up * velocity;
    }
    //Position.y = 0.0f; // <-- this one-liner keeps the user at the ground level (xz plane)
}

void Camera::process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f){
            Pitch = 89.0f;
        }
        if (Pitch < -89.0f){
            Pitch = -89.0f;
        }
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    update_camera_vectors();
}

void Camera::process_mouse_scroll(float yoffset)
{
    Zoom -= yoffset;
    if (Zoom < 1.0f){
        Zoom = 1.0f;
    }
    if (Zoom > 45.0f){
        Zoom = 45.0f;
    }
}

void Camera::update_camera_vectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front,
                                      WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}