#include "SoundModulePlayer.hpp"
namespace Sound {

ModulePlayer::ModulePlayer(Abstract::sFIO fio)
	: mod(fio)
{

}

ModulePlayer::ModulePlayer(ModulePlayer &&mov)
	: mod(std::move(mov.mod))
{

}

void ModulePlayer::operator=(ModulePlayer &&mov)
{
	this->mod = std::move(mov.mod);
}

Audio::FrameCount_T ModulePlayer::outputTo(const Audio::Output &dst)
{
	if(dst.interleavingType == Audio::InterleavingType::INTERLEAVED)
	{
		switch (dst.channelCnt) {
			case 1:
				return mod.readMono(dst.frameRate,dst.frameCnt,dst.dst);
			break;
			case 2:
				return mod.readInterleavedStereo(dst.frameRate,dst.frameCnt,dst.dst);
			break;
			case 4:
				return mod.readInterleavedQuad(dst.frameRate,dst.frameCnt,dst.dst);
			break;
		default:
			return 0;
			break;
		}
	} else {
		switch (dst.channelCnt) {
			case 1:
				return mod.readMono(dst.frameRate,dst.frameCnt,dst.dst);
			break;
			case 2:
				return mod.readStereo(dst.frameRate,dst.frameCnt,&dst.dst[0],&dst.dst[dst.frameCnt]);
			break;
			case 4:
				return mod.readQuad(dst.frameRate,dst.frameCnt,&dst.dst[0],&dst.dst[dst.frameCnt],&dst.dst[dst.frameCnt*2],&dst.dst[dst.frameCnt*3]);
			break;
		default:
			return 0;
			break;
		}
	}
}

bool ModulePlayer::isPlaying() const
{
	return true;
}

}
