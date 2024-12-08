#pragma once

// FBO with texture attatchment
class FBOTex {
public:
	FBOTex(unsigned int width, unsigned int height);
	~FBOTex();

	void bindFBO() const;
	void bindTexture(unsigned int slot) const;
	void unbind() const;

	inline unsigned int getTextureId() { return m_textureId; }

private:
	unsigned int m_fboId;
	unsigned int m_textureId;
	unsigned int m_depthBufferId;
	unsigned int m_width, m_height;
};
