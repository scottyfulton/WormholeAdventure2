#include "myShader.h"
#include "Render.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



myShader::myShader(const std::string& filepath)
	: m_FilePath(filepath), m_RenderID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
	
}

myShader::~myShader()
{
	GLCall(glDeleteProgram(m_RenderID));
}


ShaderProgramSource myShader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("shader") != std::string::npos)	//npos == invalid string position
		{
			if (line.find("vertex") != std::string::npos)
				//set mode to vertex
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				//set mode to fragment
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };

};

unsigned int myShader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();  //same as &source[0]
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//should do error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//allocate on the stack
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " myShader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;

	}

	return id;
}

unsigned int myShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, fs));
	GLCall(glAttachShader(program, vs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void myShader::Bind() const
{
	GLCall(glUseProgram(m_RenderID));
}
void myShader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void myShader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void myShader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}


void myShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));

}

int myShader::GetUniformLocation(const std::string& name)
{
	//used to check uniform cache
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall( int location = glGetUniformLocation(m_RenderID, name.c_str()));
	if (location == -1)
		std::cout << "Warning, uniform '" << name << "' doesn't exist." << std::endl;
		
	//assigns uniform to cache regardless if found
	m_UniformLocationCache[name] = location;
	return location;
}