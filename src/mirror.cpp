
// struct Framebuffer
// {
//     unsigned int quadVAO, quadVBO, framebuffer, textureColorbuffer, rbo;
// };
// Framebuffer initFrameBuffer();
// void mirror(Framebuffer &framebuff, cubeDemo &cubes, Shader &sponzaShader, Model &sponzaModel, std::vector<glm::vec3> &pointLightPositions, Grass &grass);
// void mirrorQuad(Shader &screenShader, Framebuffer const &framebuff);

// Framebuffer initFrameBuffer()
// {
//     const float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//                                   // positions   // texCoords
//                                   -0.3f, 1.0f, 0.0f, 1.0f,
//                                   -0.3f, 0.7f, 0.0f, 0.0f,
//                                   0.3f, 0.7f, 1.0f, 0.0f,

//                                   -0.3f, 1.0f, 0.0f, 1.0f,
//                                   0.3f, 0.7f, 1.0f, 0.0f,
//                                   0.3f, 1.0f, 1.0f, 1.0f};

//     // set up vertex data (and buffer(s)) and configure vertex attributes
//     // ------------------------------------------------------------------
//     unsigned int quadVAO, quadVBO;
//     glGenVertexArrays(1, &quadVAO);
//     glGenBuffers(1, &quadVBO);
//     glBindVertexArray(quadVAO);
//     glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void *>(nullptr));
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));

//     // framebuffer configuration
//     // -------------------------
//     unsigned int fb;
//     glGenFramebuffers(1, &fb);
//     glBindFramebuffer(GL_FRAMEBUFFER, fb);
//     // create a color attachment texture
//     unsigned int textureColorbuffer;
//     glGenTextures(1, &textureColorbuffer);
//     glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH * 2, SCR_HEIGHT * 2, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
//     // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
//     unsigned int rbo;
//     glGenRenderbuffers(1, &rbo);
//     glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//     glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH * 2, SCR_HEIGHT * 2);   // use a single renderbuffer object for both a depth AND stencil buffer.
//     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
//     // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
//     if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//         std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
//     return Framebuffer{quadVAO, quadVBO, fb, textureColorbuffer, rbo};
// }

// void mirror(Framebuffer &framebuff, cubeDemo &cubes, Shader &sponzaShader, Model &sponzaModel, std::vector<glm::vec3> pointLightPositions, Grass &grass)
// {
//     // bind to framebuffer and draw scene as we normally would to color texture
//     glBindFramebuffer(GL_FRAMEBUFFER, framebuff.framebuffer);
//     glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
//     glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     camera().Yaw -= 180.0f; // rotate the camera()'s yaw 180 degrees around
//     camera().Pitch -= 180.0f;
//     camera().ProcessMouseMovement(0, 0, false); // call this to make sure it updates its camera() vectors, note that we disable pitch constrains for this specific case (otherwise we can't reverse camera()'s pitch values)
//     glm::mat4 view = camera().GetViewMatrix();
//     camera().Yaw += 180.0f; // reset it back to its original orientation
//     camera().Pitch += 180.0f;
//     // rotate the camera()'s pitch 180 degrees around
//     camera().ProcessMouseMovement(0, 0, true);
//     glm::mat4 projection = glm::perspective(glm::radians(camera().Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
//     cubes.Draw(camera(), projection, view, pointLightPositions);
//     sponzaShader.use();
//     renderLights(sponzaShader, pointLightPositions);
//     // view/projection transformations
//     sponzaShader.setMat4("projection", projection);
//     sponzaShader.setMat4("view", view);
//     // render the loaded model
//     auto model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f)); // translate it down so it's at the center of the scene
//     model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
//     sponzaShader.setMat4("model", model);
//     sponzaModel.Draw(sponzaShader);
//     grass.Draw(projection, view, camera().Position);
// }

// void mirrorQuad(Shader &screenShader, Framebuffer const &framebuff)
// {
//     glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
//     screenShader.use();
//     glBindVertexArray(framebuff.quadVAO);
//     glBindTexture(GL_TEXTURE_2D, framebuff.textureColorbuffer); // use the color attachment texture as the texture of the quad plane
//     glDrawArrays(GL_TRIANGLES, 0, 6);
// }
