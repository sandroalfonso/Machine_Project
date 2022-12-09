#pragma once

class Model {
public:

    // Init VAO VBO
    GLuint VAO, VBO;

    std::vector<GLfloat> fullVertexData;

    // Initialize shader of program then 
    
	Model(const char* objFilename, int index) {
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warning, error;

        tinyobj::attrib_t attributes;

        bool success = tinyobj::LoadObj(&attributes,&shapes,&materials,&warning,&error,objFilename);

        for (int n = 0; n < shapes.size(); n++) {
            std::vector<glm::vec3> tangents;
            std::vector<glm::vec3> bitangents;
            // Iterate and Initialize indices
            for (int i = 0; i < shapes[n].mesh.indices.size(); i += 3) {
                tinyobj::index_t vData1 = shapes[n].mesh.indices[i];
                tinyobj::index_t vData2 = shapes[n].mesh.indices[i + 1];
                tinyobj::index_t vData3 = shapes[n].mesh.indices[i + 2];
                //Init vertices for v1, v2, v3
                glm::vec3 v1 = glm::vec3(
                    attributes.vertices[(vData1.vertex_index * 3)],
                    attributes.vertices[(vData1.vertex_index * 3) + 1],
                    attributes.vertices[(vData1.vertex_index * 3) + 2]
                );

                glm::vec3 v2 = glm::vec3(
                    attributes.vertices[(vData2.vertex_index * 3)],
                    attributes.vertices[(vData2.vertex_index * 3) + 1],
                    attributes.vertices[(vData2.vertex_index * 3) + 2]
                );

                glm::vec3 v3 = glm::vec3(
                    attributes.vertices[(vData3.vertex_index * 3)],
                    attributes.vertices[(vData3.vertex_index * 3) + 1],
                    attributes.vertices[(vData3.vertex_index * 3) + 2]
                );
                // Init texcoord index for uv1, uv2, uv3
                glm::vec2 uv1 = glm::vec2(
                    attributes.texcoords[(vData1.texcoord_index * 2)],
                    attributes.texcoords[(vData1.texcoord_index * 2) + 1]
                );

                glm::vec2 uv2 = glm::vec2(
                    attributes.texcoords[(vData2.texcoord_index * 2)],
                    attributes.texcoords[(vData2.texcoord_index * 2) + 1]
                );

                glm::vec2 uv3 = glm::vec2(
                    attributes.texcoords[(vData3.texcoord_index * 2)],
                    attributes.texcoords[(vData3.texcoord_index * 2) + 1]
                );
                //init deltaPos1 & 2
                glm::vec3 deltaPos1 = v2 - v1;
                glm::vec3 deltaPos2 = v3 - v1;

				//init deltaUV1 & 2
                glm::vec2 deltaUV1 = uv2 - uv1;
                glm::vec2 deltaUV2 = uv3 - uv1;

                float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));
                glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
                glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.y) * r;


                //push back tangent 3x
                tangents.push_back(tangent);
                tangents.push_back(tangent);
                tangents.push_back(tangent);
				//push back bitangent 3x
                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
            }

            for (int i = 0; i < shapes[n].mesh.indices.size(); i++) {
                tinyobj::index_t vData = shapes[n].mesh.indices[i];

                int vertexIndex = vData.vertex_index * 3;

                //Push X, Y, Z position of the vertex
                fullVertexData.push_back(attributes.vertices[vertexIndex]);
                fullVertexData.push_back(attributes.vertices[vertexIndex + 1]);
                fullVertexData.push_back(attributes.vertices[vertexIndex + 2]);

                int normalsIndex = vData.normal_index * 3;

				//Push X, Y, Z position of the normals
                fullVertexData.push_back(attributes.normals[normalsIndex]);
                fullVertexData.push_back(attributes.normals[normalsIndex + 1]);
                fullVertexData.push_back(attributes.normals[normalsIndex + 2]);

                int texCoordsIndex = vData.texcoord_index * 2;

                // Push the U, V of the Tex Coords
                fullVertexData.push_back(attributes.texcoords[texCoordsIndex]);
                fullVertexData.push_back(attributes.texcoords[texCoordsIndex + 1]);

                // Push Tangents
                fullVertexData.push_back(tangents[i].x);
                fullVertexData.push_back(tangents[i].y);
                fullVertexData.push_back(tangents[i].z);

                // Push Bitangents
                fullVertexData.push_back(bitangents[i].x);
                fullVertexData.push_back(bitangents[i].y);
                fullVertexData.push_back(bitangents[i].z);
            }
        }

        // Generate and assign for VAO, VBO, EBO
        glGenVertexArrays(1 + index, &VAO);
        glGenBuffers(1 + index, &VBO);

        // Array buffer for vertix positions
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(GL_FLOAT) * fullVertexData.size(),
            fullVertexData.data(),
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(
          0, 
          3, 
         GL_FLOAT,
         GL_FALSE,
            14 * sizeof(GL_FLOAT),
            (void*)0
        );

        GLintptr normalsPtr = 3 * sizeof(GL_FLOAT);

        glVertexAttribPointer(
            1, 
            3, 
            GL_FLOAT,
            GL_FALSE,         
            14 * sizeof(GL_FLOAT),
            (void*)normalsPtr
        );

        // Init uvPtr
        GLintptr uvPtr = 6 * sizeof(GL_FLOAT);

        glVertexAttribPointer(
            2, 
            2,
            GL_FLOAT,
            GL_FALSE,
            14 * sizeof(GL_FLOAT),
            (void*)uvPtr
        );

        GLintptr tangentPtr = 8 * sizeof(GL_FLOAT);

        glVertexAttribPointer(
            3, 
            3,
            GL_FLOAT,
            GL_FALSE,
            14 * sizeof(GL_FLOAT),
            (void*)tangentPtr
        );

        GLintptr bitangentPtr = 11 * sizeof(GL_FLOAT);

        glVertexAttribPointer(
            4, 
            3, 
            GL_FLOAT,
            GL_FALSE,
            14 * sizeof(GL_FLOAT),
            (void*)bitangentPtr
        );

        // Enable vertices
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
	}
    
    // Init VAO and shaderProgram for the drawing of Obj 
    void draw() {
        glBindVertexArray(VAO);

        // draws the obj with regards to the operations applied
        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 14);
    }

    // Delete buffers from VAO , VBO 
    void deleteBuffers() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};