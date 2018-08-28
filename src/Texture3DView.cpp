#include "Texture3DView.hpp"

#include <iostream>

Texture3DView::Texture3DView(std::string id,
	Texture3D const& source_texture,
	TextureLayout const& layout,
	GLuint minlevel,
	GLuint numlevels,
	GLuint minlayer,
	GLuint numlayers)
	:Texture(id,layout.internal_format,layout.format,layout.type, layout.levels)
{
	glGenTextures(1, &m_name);

	glBindTexture(GL_TEXTURE_3D, m_name);

	for (auto& pname_pvalue : layout.int_parameters)
		glTexParameteri(GL_TEXTURE_3D, pname_pvalue.first, pname_pvalue.second);

	for (auto& pname_pvalue : layout.float_parameters)
		glTexParameterf(GL_TEXTURE_3D, pname_pvalue.first, pname_pvalue.second);

	glTextureView(m_name, GL_TEXTURE_3D, source_texture.getName(), m_internal_format, minlevel, numlevels, minlayer, numlayers);

	glBindTexture(GL_TEXTURE_3D, 0);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		// "Do something cop!"
		std::cerr << "GL error during 3D texture view creation: " << err << std::endl;
	}
}

void Texture3DView::bindTexture() const
{
	glBindTexture(GL_TEXTURE_3D, m_name);
}

void Texture3DView::bindImage(GLuint location, GLenum access) const
{
	glBindImageTexture(location, m_name, 0, GL_TRUE, 0, access, m_internal_format);
}

TextureLayout Texture3DView::getTextureLayout() const
{
	return TextureLayout(m_internal_format, m_width, m_height, m_depth, m_format, m_type, m_levels);
}

unsigned int Texture3DView::getWidth()
{
	return m_width;
}

unsigned int Texture3DView::getHeight()
{
	return m_height;
}

unsigned int Texture3DView::getDepth()
{
	return m_depth;
}