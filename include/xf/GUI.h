#pragma once


#include <minecraft/util/other.h>

#include "DrawHelper.h"

#include <minecraft/client/file/FileOutputStream.h>
#include <minecraft/client/file/FileInputStream.h>
#include "minecraft/client/resource/wstring.h"

#include <minecraft/client/app/System.h>




namespace xf {
		
        class InfoScreen {
        public:

            InfoScreen() = default;
			float DebugScale = 1.0f;
			
			uint32_t TimerMode = 0;
			uint64_t StartTime = 0x0;
			uint64_t CurrentTime = 0x0;

            void send() {
                mc::Minecraft* minecraft = mc::Minecraft::getInstance();
                mc::ClientPacketListener* listener = minecraft->getConnection(0);
                mc::LocalPlayer* lPlayer = minecraft->thePlayer;

				drawCoords();
            }

            void onTick() {
                xf::GUI::DrawHelper::renderSetup();
                send();
            }

        protected:
			
			template<typename... Args>
			void DrawDebugLine(uint32_t size, const wchar_t* inputString, uint32_t line, mc::Font* font, Args... args)
			{
				wchar_t* Text = _new<wchar_t>(size);
				mc_swprintf(Text, size, inputString, args...);
				int newTextWidth = (font->width(Text)*3) + 9;
				
				mc::Tesselator* tess = mc::Tesselator::getInstance();
				
				mc::GlStateManager::disableTexture();
				tess->rendersquare(mc::toFloat((WIDTH) - newTextWidth        - 3),      mc::toFloat(5.0f * (3.0f * line))  - 3, newTextWidth        + 3, mc::toFloat(5.0f * (6.0f * 1)) - 1, 0x050505, 0x50);
				
				xf::GUI::DrawHelper::DisplayText(font, Text,   3.0f, mc::toFloat((WIDTH) - newTextWidth),        mc::toFloat(5.0f * (3.0f * line)));
			}
			
			
            void drawCoords() {
                mc::Font* font = mc::Minecraft::getInstance()->defaultFonts;
				
				if(TimerMode == 1)
					CurrentTime = mc::System::processTimeInMilliSecs();
                // gets system time and subtracts from time the world starts
                long milli = CurrentTime - StartTime;
                //3600000 milliseconds in an hour
                long hr = milli / 3600000;
                milli = milli - 3600000 * hr;
                //60000 milliseconds in a minute
                long min = milli / 60000;
                milli = milli - 60000 * min;

                //1000 milliseconds in a second
                long sec = milli / 1000;
                milli = milli - 1000 * sec;
				
				DrawDebugLine(0x40, L"%d:%d:%d:%d", 1, font, hr, min, sec, milli);
				
				
				
            }
			


    
};}