#pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;
	using TextureAssetName = String;

	/// <summary>
	/// �p���p������̂悤�ȃA�j���[�V����
	/// </summary>
	class AssetAnime
	{

	private:

		TextureAssetName m_name;

		size_t m_size;

		Array<int32> m_duration;

		int m_index;

		Stopwatch m_stopwatch;

	public:

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		AssetAnime();

		/// <summary>
		/// s3d::TextureAsset����asc::Anime���쐬���܂��B
		/// </summary>
		/// <param name="name">
		/// Texture �A�Z�b�g�̓o�^��
		/// </param>
		/// <param name="size">
		/// �e�N�X�`���Ɋ܂܂��R�}��
		/// </param>
		/// <param name="duration">
		/// 1�R�}�̕`�掞��[�~���b]
		/// </param>
		AssetAnime(const TextureAssetName& name, size_t size, int32 duration, bool startImmediately = true);

		/// <summary>
		/// s3d::TextureAsset����asc::Anime���쐬���܂��B
		/// </summary>
		/// <param name="name">
		/// Texture �A�Z�b�g�̓o�^��
		/// </param>
		/// <param name="size">
		/// �e�N�X�`���Ɋ܂܂��R�}��
		/// </param>
		/// <param name="duration">
		/// �e�R�}�̕`�掞��[�~���b]
		/// </param>
		AssetAnime(const TextureAssetName& name, size_t size, const Array<int32>& duration, bool startImmediately = true);

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~AssetAnime();

		/// <summary>
		/// 1�R�}�̕��i�s�N�Z���j
		/// </summary>
		__declspec(property(get = _get_width)) uint32 width;

		/// <summary>
		/// 1�R�}�̍����i�s�N�Z���j
		/// </summary>
		__declspec(property(get = _get_height)) uint32 height;

		/// <summary>
		/// ������Texture �A�Z�b�g���v�����[�h���܂��B
		/// </summary>
		/// <returns>
		/// �v�����[�h�ɐ��������ꍇ true, ����ȊO�̏ꍇ�� false
		/// </returns>
		bool preload() { return TextureAsset::Preload(m_name); };

		/// <summary>
		/// ������Texture �A�Z�b�g�������[�X���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void release() { TextureAsset::Release(m_name); }

		/// <summary>
		/// �e�N�X�`������ł͂Ȃ�����Ԃ��܂��B
		/// </summary>
		/// <returns>
		/// �e�N�X�`������ł͂Ȃ��ꍇ true, ����ȊO�̏ꍇ�� false
		/// </returns>
		explicit operator bool() const { return !isEmpty(); }

		/// <summary>
		/// �����̃e�N�X�`���n���h���� ID �������܂��B
		/// </summary>
		HandleIDType id() const { return TextureAsset(m_name).id(); };

		/// <summary>
		/// �����̃e�N�X�`�����󂩂ǂ����������܂��B
		/// </summary>
		/// <returns>
		/// �e�N�X�`������ł͂Ȃ��ꍇ true, ����ȊO�̏ꍇ�� false
		/// </returns>
		bool isEmpty() const { return TextureAsset(m_name).isEmpty(); };

		/// <summary>
		/// �A�j���[�V�������J�n���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void start() { m_stopwatch.start(); }

		/// <summary>
		/// �A�j���[�V���������쒆�ł��邩�������܂��B
		/// </summary>
		/// <remarks>
		/// �A�j���[�V�������J�n����Ă���A�܂��͊J�n��ꎞ��~���ł���ꍇ true, ����ȊO�̏ꍇ�� false
		/// </remarks>
		bool isActive() const noexcept { return m_stopwatch.isActive(); }

		/// <summary>
		/// �A�j���[�V�������ꎞ��~���ł��邩�������܂��B
		/// </summary>
		/// <remarks>
		/// �A�j���[�V�������J�n��ꎞ��~���ł���ꍇ true, ����ȊO�̏ꍇ�� false
		/// </remarks>
		bool isPaused() const noexcept { return m_stopwatch.isPaused(); }

		/// <summary>
		/// �A�j���[�V�������ꎞ��~���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void pause() { m_stopwatch.pause(); }

		/// <summary>
		/// �A�j���[�V�������ꎞ��~���ł���ꍇ�A�ĊJ���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void resume() { m_stopwatch.resume(); }

		/// <summary>
		/// �A�j���[�V�������~���A������ԂɃ��Z�b�g���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void reset() noexcept;

		/// <summary>
		/// ������ԂɃ��Z�b�g���āA�A�j���[�V�������J�n���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void restart();

		/// <summary>
		/// �P�R�}�̕`�掞�Ԃ�ݒ肵�܂��B
		/// </summary>
		/// <param name="duration">
		/// 1�R�}�̕`�掞��[�~���b]
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void setDuration(int32 duration);

		/// <summary>
		/// �e�R�}�̕`�掞�Ԃ�ݒ肵�܂��B
		/// </summary>
		/// <param name="duration">
		/// �e�R�}�̕`�掞��[�~���b]
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void setDuration(const Array<int32>& duration);

		/// <summary>
		/// ����̃R�}�ɔ�т܂��B
		/// </summary>
		/// <param name="duration">
		/// ��񂾐�̃R�}�̌o�ߎ���
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void jump(int index, const MillisecondsF& time = MillisecondsF(0.0));

		/// <summary>
		/// �A�j���[�V�������X�V���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void update();

		/// <summary>
		/// �`�悷��TextureRegion���擾���܂��B
		/// </summary>
		/// <returns>
		/// �`�悷��TextureRegion
		/// </returns>
		const TextureRegion get() const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Color& diffuse = Palette::White) const
		{
			return get().draw(diffuse);
		}

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(double x, double y, const Color& diffuse = Palette::White) const
		{
			return get().draw(x, y, diffuse);
		}

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const
		{
			return get().draw(pos, diffuse);
		}

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const
		{
			return get().drawAt(x, y, diffuse);
		}

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const
		{
			return get().drawAt(pos, diffuse);
		}

		/// <summary>
		/// s3d::Texture::operator ()
		/// </summary>
		const TextureRegion operator ()(double x, double y, double w, double h) const
		{
			return TextureAsset(m_name)(m_index * width + x, y, w, h);
		}

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(double u, double v, double w, double h) const
		{
			return TextureAsset(m_name).uv((m_index + u) / m_size, v, w / m_size, h);
		}

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(const RectF& rect) const
		{
			return TextureAsset(m_name).uv(rect.movedBy(m_index * width, 0.0));
		}

		/// <summary>
		/// s3d::Texture::mirror
		/// </summary>
		const TextureRegion mirror() const
		{
			return get().mirror();
		}

		/// <summary>
		/// s3d::Texture::flip
		/// </summary>
		const TextureRegion flip() const
		{
			return get().flip();
		}

		/// <summary>
		/// s3d::Texture::scaling
		/// </summary>
		const TextureRegion scale(double scaling) const
		{
			return get().scale(scaling);
		}

		/// <summary>
		/// s3d::Texture::scaling
		/// </summary>
		const TextureRegion scale(double xScaling, double yScaling) const
		{
			return get().scale(xScaling, yScaling);
		}

		/// <summary>
		/// s3d::Texture::scaling
		/// </summary>
		const TextureRegion scale(const Vec2& scaling) const
		{
			return get().scale(scaling);
		}

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resize(double width, double height) const
		{
			return get().resize(width, height);
		}

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resize(const Vec2& size) const
		{
			return get().resize(size);
		}

		/// <summary>
		/// s3d::Texture::rotate
		/// </summary>
		const TexturedQuad rotate(double radian) const
		{
			return get().rotate(radian);
		}

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotateAt(double x, double y, double radian) const
		{
			return get().rotateAt(x, y, radian);
		}

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotateAt(const Vec2& pos, double radian) const
		{
			return get().rotateAt(pos, radian);
		}

		uint32 _get_width() const { return TextureAsset(m_name).width / static_cast<uint32>(m_size); }

		uint32 _get_height() const { return TextureAsset(m_name).height; }
	};
}
