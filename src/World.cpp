#include <World.h>
#include <Model.h>
#include <stb_image.h>
#include <stdlib.h>

World::World() {
    treeModel = std::make_unique<Model>("C:/Users/Vitor/Documents/SlenderProject/images/Tree2/Tree.obj");
}

World::~World() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

unsigned int World::initTextures(char const* path) {

    glGenTextures(1, &texture);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }
    else
    {
        std::cout << "ERROR LOADING PATH: " << path << std::endl;
    }

    stbi_image_free(data);


    return texture;
}

void World::initBuffers() {
    float vertices[] = {
        // positions          //normal            // texture coords
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 10.0f,   30.0f, 30.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   30.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 30.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void World::transformGround(Shader* shader) {
    glm::mat4 model = glm::mat4(1.0f);

    model = rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = scale(model, glm::vec3(200.0f, 200.0f, 1.0f));

    shader->setMat4("model", model);
}

void World::drawGround(Shader* shader) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    glEnableClientState(GL_VERTEX_ARRAY);

    transformGround(shader);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}

// Sets the tree's position, scale, and rotation(to make some diversity)
// x and z set the position
void World::transformTree(Shader* shader, int x, int z) {
    glm::mat4 model = glm::mat4(1.0f);
    float treeRotateOffset = rand() % 360;
    float treeScaleOffset = rand() % 3 + 2;

    model = translate(model, glm::vec3(x, 0.0f, z));
    model = scale(model, glm::vec3(treeScaleOffset));
    model = rotate(model, glm::radians(treeScaleOffset), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->setMat4("model", model);
}

// Draws the trees
// (rand() % 50) gives a random number to the offset everytime a tree is drawn
// srand(0) makes the trees go from 0 so they dont teleport
void World::drawTrees(Shader& shader) {
    srand(0);

    for (int x = -50; x < forestSize; x += treeSpacing) {
        for (int z = -50; z < forestSize; z += treeSpacing) {
            int xOffset = rand() % 50;
            int zOffset = rand() % 50;

            transformTree(&shader, (x + xOffset), (z + zOffset));
            treeModel->Draw(shader);
        }
    }
}

