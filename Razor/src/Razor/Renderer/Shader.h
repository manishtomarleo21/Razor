#pragma once

#include <string>


namespace Razor
{
	class Shader
	{
	public:
		//Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	/*	void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);*/
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	};

}