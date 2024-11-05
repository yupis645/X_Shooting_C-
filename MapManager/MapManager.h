#ifndef MAPMANAGER_H
#define MAPMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              �n�\�̃e�N�X�`���̔z�u�Ȃǂ��Ǘ�����N���X
// 
// �}�b�v�̃^�C���`�b�v�ԍ����L�������z��ƒn�ʂ̃e�N�X�`���������A�}�b�v�̃X�N���[���ƕ`�ʂ��s��
// 1�}�b�v�ɕt���X�^�[�g�G���A�ł���X�̃}�b�v�����킹�� (MAP_H * MAP_W) * 5 �̍L��������
// �`�ʂ̍ۂɂ̓X�N���[���̕`��͈͂ł��� MAP_H * MAP_W �̍L���ŋ�؂�A
//      primarymap��secondarymap�Ƃ�����̔z����g���Č��݂ɕ`�ʂ��Ă���B
// �����o�ϐ� mapchip �ɂ�int�ԍ��ɉ������n�ʂ̃e�N�X�`���������Ă���
// �����o�ϐ� mapdata �ɂ͕����O�̂P�}�b�v���̂܃v�`�b�v�̔z�u�������Ă���B
//      primarymap��secondarymap�� mapdata ����}�b�v�`�b�v�̔z�u���󂯎��
//----------------------------------------------------------------------------------------------------

class ResourceManager;
class GameTexture;
class SpriteRenderer;


#include "IMapManager.h"


class MapManager : public IMapManager {
public:
    MapManager(std::shared_ptr<ResourceManager> rm);        //�R���X�g���N�^
   

    int Init() override;       //������
    int Update() override;     //�X�V
    int Draw() override;       //�`��

    bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)override;      //�}�b�v�`�b�v�摜�̃��[�h

    void SwapMapdata();       //int�z���mapdata���X�V����
 
    const std::vector<int>& GetDrawMapData() const override { return mapdata; } //�}�b�v�`�b�v��int�z���getter
    void SetDrawMapData(std::vector<int> copyvector) { mapdata = copyvector; }  //�}�b�v�`�b�v��int�z���setter

    ~MapManager() = default;        ///�f�X�g���N�^


private:
    int currentnumber;			    //���݂̃X�e�[�W�ԍ����L������
    int currentpartition;			//�X�e�[�W�𕪊��������Ō��݂͉��Ԗڂ�������

    std::shared_ptr<GameTexture> mapchip;       //�}�b�v�`�b�v�̉摜��ۊǂ��Ă����ϐ�
    std::vector<int> backmap;               
    std::vector<int> mapdata;           //�}�b�v�`�b�v�̔z�u���Ǘ�����int�z��

    MapStatus primarymap;       //���������}�b�v�f�[�^��ێ����Ă����ϐ�
    MapStatus secondarymap;     //���������}�b�v�f�[�^��ێ����Ă����ϐ�
     
    std::shared_ptr<SpriteRenderer> render_;
    std::shared_ptr<ResourceManager> resource_;

    void MapDataUpdate(MapStatus& map, int startprogress);       //�`�ʂ���}�b�v�̔z����X�V����
};




#endif //MAPMANAGER_H