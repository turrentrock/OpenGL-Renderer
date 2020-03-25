#include "Box.h"

#include <Camera.h>
#include <GL/glew.h>
#include <imgui/imgui.h>

#include <string>
#include <sstream>

namespace material {

	unsigned int Material::m_MaterialId_Count = 0;

	Material::Material() {

		/* Model Init */
		m_Rotate = {0.0f,0.0f,0.0f};
		m_Scale = {1.0f,1.0f,1.0f};
		m_Translate = {0.0f,0.0f,0.0f};
		m_Model = glm::mat4(1.0f);

		m_MaterialId = m_MaterialId_Count;
		m_MaterialId_Count += 1;

	}

	Material::~Material(){
		
	}

	void Material::OnUpdate(){
		m_Model = glm::mat4(1.0f);

		m_Model = glm::translate(m_Model, m_Translate);

		m_Model = glm::rotate(m_Model, glm::radians(m_Rotate.z), glm::vec3(0.0f,0.0f,1.0f));
		m_Model = glm::rotate(m_Model, glm::radians(m_Rotate.y), glm::vec3(0.0f,1.0f,0.0f));
		m_Model = glm::rotate(m_Model, glm::radians(m_Rotate.x), glm::vec3(1.0f,0.0f,0.0f));

		m_Model = glm::scale(m_Model,m_Scale);

	}
	glm::mat4 Material::OnRender(){

		Camera* camera = Camera::getCurrentCamera();

		if (!camera)
			return glm::mat4(0.0f);

		glm::mat4 mvp = camera->getVP() * m_Model;

		return mvp;

	}
	void Material::OnImGuiRender(){

		std::stringstream ss[3];

		ss[0] << m_MaterialId << " Translation";
		ss[1] << m_MaterialId << " Rotation";
		ss[2] << m_MaterialId << " Scale";

		ImGui::SliderFloat3(ss[0].str().c_str(), &m_Translate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3(ss[1].str().c_str(), &m_Rotate.x, -180.0f, 180.0f);
		ImGui::SliderFloat3(ss[2].str().c_str(), &m_Scale.x, 0.0f, 5.0f);
		OnUpdate();
	}

}