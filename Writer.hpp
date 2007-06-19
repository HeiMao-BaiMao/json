/**
 * �o�͏����p�C���^�[�t�F�[�X
 */
class IWriter {
public:
	int indent;
	IWriter() {
		indent = 0;
	}
	virtual ~IWriter(){};
	virtual void write(const tjs_char *str) = 0;
	virtual void write(tjs_char ch) = 0;
	virtual void write(tTVReal) = 0;
	virtual void write(tTVInteger) = 0;

	inline void newline() {
		write((tjs_char)'\n');
		for (int i=0;i<indent;i++) {
			write((tjs_char)' ');
		}
	}

	inline void addIndent() {
		indent++;
		newline();
	}

	inline void delIndent() {
		indent--;
		newline();
	}
};

/**
 * ������o��
 */
class IStringWriter : public IWriter {

public:
	ttstr buf;
	/**
	 * �R���X�g���N�^
	 */
	IStringWriter(){};

	virtual void write(const tjs_char *str) {
		buf += str;
	}

	virtual void write(tjs_char ch) {
		buf += ch;
	}

	virtual void write(tTVReal num) {
		tTJSVariantString *str = TJSRealToString(num);
		buf += str;
		str->Release();
	}

	virtual void write(tTVInteger num) {
		tTJSVariantString *str = TJSIntegerToString(num);
		buf += str;
		str->Release();
	}
};

/**
 * �t�@�C���o��
 */
class IFileWriter : public IWriter {

	/// �o�̓o�b�t�@
	ttstr buf;
	/// �o�̓X�g���[��
	iTJSTextWriteStream *stream;

public:

	/**
	 * �R���X�g���N�^
	 */
	IFileWriter(const tjs_char *filename) {
		stream = TVPCreateTextStreamForWrite(filename, TJS_W(""));
	}

	/**
	 * �f�X�g���N�^
	 */
	~IFileWriter() {
		if (stream) {
			if (buf.length() > 0) {
				stream->Write(buf);
				buf.Clear();
			}
			stream->Destruct();
		}
	}

	virtual void write(const tjs_char *str) {
		if (stream) {
			buf += str;
			if (buf.length() >= 1024) {
				stream->Write(buf);
				buf.Clear();
			}
		}
	}

	virtual void write(tjs_char ch) {
		buf += ch;
	}

	virtual void write(tTVReal num) {
		tTJSVariantString *str = TJSRealToString(num);
		buf += str;
		str->Release();
	}

	virtual void write(tTVInteger num) {
		tTJSVariantString *str = TJSIntegerToString(num);
		buf += str;
		str->Release();
	}
};
