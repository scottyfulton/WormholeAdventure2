#pragma once
#include <string>
#include <unordered_map>



struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class myShader
{
private:
	std::string m_FilePath;
	unsigned int m_RenderID;
	//caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	myShader(const std::string& filepath);
	~myShader();

	void Bind() const;
	void UnBind() const;

	//set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);

};