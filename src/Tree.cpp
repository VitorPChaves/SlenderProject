#include <Tree.h>

Tree::Tree() : treeBody(BoundingBox(glm::vec3(0), glm::vec3(0)), false)
{
	treeModel = std::make_unique<Model>("../images/Tree2/Tree.obj");
	//treeBody.setPosition(treeP[cont]);
    generateTreesTransforms();
}

void Tree::generateTreesTransforms() {
    srand(0);

    for (int x = -50; x < forestSize; x += treeSpacing) {
        for (int z = -50; z < forestSize; z += treeSpacing) {

            glm::mat4 model = glm::mat4(1.0f);

            int xOffset = rand() % 50;
            int zOffset = rand() % 50;
            float treeRotateOffset = rand() % 360;
            float treeScaleOffset = rand() % 3 + 2;

            model = translate(model, glm::vec3(x + xOffset, 0.0f, z + zOffset));
            model = scale(model, glm::vec3(treeScaleOffset));
            model = rotate(model, glm::radians(treeScaleOffset), glm::vec3(0.0f, 1.0f, 0.0f));

            treeTransform.push_back(model);            
        }
    }
}

void Tree::drawTrees(Shader& shader) {

    //for (int i = 0; i < treeTransform.size(); ++i) {
    //auto m = treeTransform[i];
    for each (const auto& m in treeTransform) {
        shader.setMat4("model", m);
        treeModel->Draw(shader);
    }

}

// Gerar uma posição randomica
// Armazenar essa posição
// Passar as posições
// Desenhar