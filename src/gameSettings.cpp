#include <gameSettings.h>

gameSettings::gameSettings(Shader& shader, Camera& camera, Model& model)
	: shaderProgram(shader), camera(camera), model(model)
	{ }

void gameSettings::showSlender(int time_elaps) {
	if (time_elaps >= frequency) {
		times += 0.5;
		frequency += (times * 10);
		
		//cout << "passs here" << endl;
		//cout << "passs here" << endl;
		//cout << "passs here" << endl;

		shaderProgram.use();
		camera.transform(&shaderProgram);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram.setMat4("model", model);
		model.Draw(shaderProgram);
	}
}