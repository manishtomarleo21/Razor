#type vertex
#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec2 a_TexCoord;
			layout(location = 3) in float a_TexIndex;
			layout(location = 4) in float a_TilingFactor;
		
			uniform mat4 u_ViewProjection;
			

			out vec4 v_Color;
			out vec2 v_TexCoord;
			out float v_TexIndex;
			out float v_TilingFactor;

			void main()
			{
				v_Color = a_Color;
				v_TexCoord = a_TexCoord;
				v_TexIndex = a_TexIndex;
				v_TilingFactor = a_TilingFactor;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

#type fragment
#version 330 core
			
			layout(location = 0) out vec4 color;
			layout(location = 1) out int color2;

			in vec4 v_Color;
			in vec2 v_TexCoord;
			in float v_TexIndex;
			in float v_TilingFactor;

			
			uniform sampler2D u_Textures[32];

			void main()
			{
				 // Flip the y-coordinate of v_TexCoord to correct the upside-down texture
				vec2 flippedTexCoord = vec2(v_TexCoord.x, 1.0 - v_TexCoord.y);
			
				//Custom if not work or any issue use v_TexCoord in place of flippedTexCore and delete above line
				color = texture(u_Textures[int(v_TexIndex)], flippedTexCoord * v_TilingFactor) * v_Color;
				
				color2 = 50;
			}