#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class Light
{
public:
	glm::vec3 lightPos;
	glm::vec3 lightColor;
    
    float ambientStr;
    glm::vec3 ambientColor;
    float specPhong;
    float specStr;
    float intensity;

    // Constructors
    Light(glm::vec3 position, 
            glm::vec3 color, 
            float amb_str, 
            glm::vec3 amb_clr, 
            float spc_str, 
            float spc_phn) {

        lightPos = position;
        lightColor = color;
        specStr = spc_str;
        specPhong = spc_phn;
        ambientStr = amb_str;
        ambientColor = amb_clr;
        intensity = 6.0f;
    }

    glm::vec3 getLightPos() {
        return lightPos;
    }

    glm::vec3 getLightColor() {
        return lightColor;
    }

    float getAmbientStr() {
        return ambientStr;
    }

    glm::vec3 getAmbientColor() {
        return ambientColor;
    }

    float getSpecularStrength() {
        return specStr;
    }

    float getSpecularPhong() {
        return specPhong;
    }

    float getIntensity() {
        return intensity;
    }

    void cycleIntensity() {
        if (intensity == 6.0f) {
            intensity = 8.0f;   // Cycle Intensity set to Medium
            printf("Intensity set to: Medium\n");
        }

        else if (intensity == 8.0f) {
            intensity = 10.0f;  // Cycle Intensity set to High
			printf("Intensity set to: High\n");
        }

        else if (intensity == 10.0f) {
            intensity = 6.0f; // Cycle Intensity set to Low
			printf("Intensity set to: Low\n");
        }
      
    }

    void setLightPos(glm::vec3 position) {
        lightPos = position;
    }


};

