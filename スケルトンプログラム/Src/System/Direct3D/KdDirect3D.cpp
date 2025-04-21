#include "System/KdSystem.h"

void KdDirect3D::GetViewport(Math::Viewport & out) const
{
	UINT numVPs = 1;
	D3D11_VIEWPORT vp;
	m_pDeviceContext->RSGetViewports(&numVPs, &vp);
	out = vp;
}

bool KdDirect3D::Init(HWND hWnd, int w, int h, bool deviceDebug, std::string& errMsg)
{
	HRESULT hr;

	//=====================================================
	// �t�@�N�g���[�쐬(�r�f�I �O���t�B�b�N�̐ݒ�̗񋓂�w��Ɏg�p�����I�u�W�F�N�g)
	//=====================================================
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&m_pGIFactory));
	if (FAILED(hr)) {
		errMsg = "�t�@�N�g���[�쐬���s";

		Release();
		return false;
	}

	//=====================================================
	//�f�o�C�X����(��Ƀ��\�[�X�쐬���Ɏg�p����I�u�W�F�N�g)
	//=====================================================
	UINT creationFlags = 0;

	if (deviceDebug) {
		// Direct3D�̃f�o�b�O��L���ɂ���(�������d�����ׂ����G���[���킩��)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1  ShaderModel 5
		D3D_FEATURE_LEVEL_11_0,	// Direct3D 11    ShaderModel 5
		D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1  ShaderModel 4
		D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0  ShaderModel 4
		D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3   ShaderModel 3
		D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2   ShaderModel 3
		D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1   ShaderModel 3
	};

	// �f�o�C�X�ƂŃf�o�C�X�R���e�L�X�g���쐬
	hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				creationFlags,
				featureLevels,
				_countof(featureLevels),
				D3D11_SDK_VERSION,
				&m_pDevice,
				nullptr,
				&m_pDeviceContext);
	if FAILED( hr )
	{
		errMsg = "Direct3D11�f�o�C�X�쐬���s";

		Release();
		return false;
	}

	//=====================================================
	// �X���b�v�`�F�C���쐬(�t�����g�o�b�t�@�ɕ\���\�ȃo�b�N�o�b�t�@��������)
	//=====================================================
	DXGI_SWAP_CHAIN_DESC	DXGISwapChainDesc = {};		// �X���b�v�`�F�[���̐ݒ�f�[�^
	DXGISwapChainDesc.BufferDesc.Width = w;
	DXGISwapChainDesc.BufferDesc.Height = h;
	DXGISwapChainDesc.BufferDesc.RefreshRate.Numerator  = 0;
	DXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	DXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	DXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;// DXGI_MODE_SCALING_CENTERED;	// DXGI_MODE_SCALING_UNSPECIFIED
	DXGISwapChainDesc.SampleDesc.Count = 1;
	DXGISwapChainDesc.SampleDesc.Quality = 0;
	DXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	DXGISwapChainDesc.BufferCount = 2;
	DXGISwapChainDesc.OutputWindow = hWnd;
	DXGISwapChainDesc.Windowed = TRUE;
	DXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	DXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	if(FAILED(m_pGIFactory->CreateSwapChain(m_pDevice, &DXGISwapChainDesc, &m_pGISwapChain))){
		errMsg = "�X���b�v�`�F�C���쐬���s";

		Release();
		return false;
	}

	// �X���b�v�`�F�C������o�b�N�o�b�t�@�擾
	ID3D11Texture2D* pBackBuffer;
	if (FAILED(m_pGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer))) {
		errMsg = "�o�b�N�o�b�t�@�擾���s";

		Release();
		return false;
	}

	// �o�b�N�o�b�t�@�p�̃����_�[�^�[�Q�b�g�r���[�쐬
	{
		D3D11_TEXTURE2D_DESC desc;
		pBackBuffer->GetDesc(&desc);

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = desc.Format;	// Format
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;			// �P�i�e�N�X�`��

		// �����_�[�^�[�Q�b�g�r���[�쐬
		HRESULT hr = m_pDevice->CreateRenderTargetView(pBackBuffer, &rtvDesc, &m_rtvBackBuffer);
		if (FAILED(hr)) {
			errMsg = "�o�b�N�o�b�t�@�쐬���s";
			Release();
			return false;
		}
	}

	pBackBuffer->Release();

	/*
	// ALT+Enter�Ńt���X�N���[���s�ɂ���
	{
		IDXGIDevice* pDXGIDevice;
		m_pDevice->QueryInterface<IDXGIDevice>(&pDXGIDevice);

		IDXGIAdapter* pDXGIAdapter;
		pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

		IDXGIFactory* pIDXGIFactory;
		pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pIDXGIFactory);

		pIDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);

		pDXGIDevice->Release();
		pDXGIAdapter->Release();
		pIDXGIFactory->Release();
	}
	*/

	//=========================================================
	// Z�o�b�t�@�쐬
	//=========================================================
	{
		// �o�b�t�@�쐬
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Format = DXGI_FORMAT_R32_TYPELESS;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		desc.Width = (UINT)w;
		desc.Height = (UINT)h;
		desc.CPUAccessFlags = 0;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		ID3D11Texture2D* buffer = nullptr;
		HRESULT hr = m_pDevice->CreateTexture2D(&desc, nullptr, &buffer);
		if (FAILED(hr)) {
			errMsg = "Z�o�b�t�@�쐬���s";
			Release();
			return false;
		}

		// �r���[�쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC dpDesc = {};
		dpDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dpDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dpDesc.Texture2D.MipSlice = 0;

		// �f�v�X�X�e���V���r���[�쐬
		hr = m_pDevice->CreateDepthStencilView(buffer, &dpDesc, &m_dsvZBuffer);
		if (FAILED(hr)) {
			errMsg = "Z�o�b�t�@�쐬���s";
			Release();
			return false;
		}

		buffer->Release();
	}
	/*
	m_texDepthStencil = std::make_shared<KdTexture>();
	if (m_texDepthStencil->CreateDepth(w, h, DXGI_FORMAT_R24G8_TYPELESS) == false) {
		errMsg = "Z�o�b�t�@�쐬���s";
		Release();
		return false;
	}
	*/

	//=========================================================
	// �o�b�N�o�b�t�@�AZ�o�b�t�@ ���f�o�C�X�R���e�L�X�g�փZ�b�g����
	//=========================================================
	{
		ID3D11RenderTargetView* rtvs[] = { m_rtvBackBuffer };
		m_pDeviceContext->OMSetRenderTargets(1, rtvs, m_dsvZBuffer);
	}

	//=========================================================
	// �r���[�|�[�g�̐ݒ�
	//=========================================================
	{
		// �r���[�|�[�g�̐ݒ�
		D3D11_VIEWPORT vp;
		vp.Width = (float)w;
		vp.Height = (float)h;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pDeviceContext->RSSetViewports(1, &vp);
	}

	//=========================================================
	// �u�����h�X�e�[�g�Z�b�g���Z�b�g���Ă���
	//=========================================================

	// �u�����h�X�e�[�g�Z�b�g
	SetBlendState(BlendMode::Alpha);
	// �T���v���[�X�e�[�g�Z�b�g
	SetSamplerState(0, SamplerFilterMode::Anisotropic, 4, SamplerAddressingMode::Wrap, false);
	SetSamplerState(1, SamplerFilterMode::Anisotropic, 4, SamplerAddressingMode::Clamp, false);
	// ���X�^���C�U�[�X�e�[�g�Z�b�g
	SetRasterizerState(D3D11_CULL_BACK, D3D11_FILL_SOLID, true, false);
	// �[�x�X�e���V���X�e�[�g�Z�b�g
	SetDepthStencilState(true, true);

	//=========================================================
	// 1x1�̔��e�N�X�`���쐬
	//=========================================================
	{
		// 0xAABBGGRR
		auto col = Math::Color(1, 1, 1, 1).RGBA();
		D3D11_SUBRESOURCE_DATA srd;
		srd.pSysMem = &col;
		srd.SysMemPitch = 4;
		srd.SysMemSlicePitch = 0;

		m_texWhite = std::make_shared<KdTexture>();
		m_texWhite->Create(1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 1, &srd);
	}

	return true;
}

void KdDirect3D::Release()
{
	m_tempVertexBuffer.Release();

	KdSafeRelease(m_rtvBackBuffer);
	KdSafeRelease(m_dsvZBuffer);

	KdSafeRelease(m_pGISwapChain);
	KdSafeRelease(m_pGIAdapter);
	KdSafeRelease(m_pGIFactory);
	KdSafeRelease(m_pDeviceContext);
	KdSafeRelease(m_pDevice);

	m_texWhite = nullptr;
}

void KdDirect3D::SetDepthStencilState(bool enable, bool writeEnable)
{
	// �X�e�[�g�쐬
	ID3D11DepthStencilState* state = KdCreateDepthStencilState(m_pDevice, enable, writeEnable);

	// �f�o�C�X�R���e�L�X�g�փZ�b�g
	GetDevContext()->OMSetDepthStencilState(state, 0);

	// ���(�����ł͎Q�ƃJ�E���^��-1����邾��)
	state->Release();
}

void KdDirect3D::SetRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool depthClipEnable, bool scissorEnable)
{
	// �X�e�[�g�쐬
	ID3D11RasterizerState* state = KdCreateRasterizerState(m_pDevice, cullMode, fillMode, depthClipEnable, scissorEnable);

	// �f�o�C�X�R���e�L�X�g�փZ�b�g
	GetDevContext()->RSSetState(state);

	// ���(�����ł͎Q�ƃJ�E���^��-1����邾��)
	state->Release();
}

void KdDirect3D::SetSamplerState(int slotNo, SamplerFilterMode filterType, UINT maxAnisotropy, SamplerAddressingMode addressingMode, bool comparisonModel)
{
	// �X�e�[�g�쐬
	ID3D11SamplerState* state = KdCreateSamplerState(m_pDevice, filterType, maxAnisotropy, addressingMode, comparisonModel);

	// �e�V�F�[�_�փZ�b�g
	GetDevContext()->VSSetSamplers(slotNo, 1, &state);
	GetDevContext()->PSSetSamplers(slotNo, 1, &state);
	GetDevContext()->GSSetSamplers(slotNo, 1, &state);
	GetDevContext()->CSSetSamplers(slotNo, 1, &state);

	// ���(�����ł͎Q�ƃJ�E���^��-1����邾��)
	state->Release();
}

void KdDirect3D::SetBlendState(BlendMode mode)
{
	// �X�e�[�g�쐬
	ID3D11BlendState* state = KdCreateBlendState(m_pDevice, mode);

	// �f�o�C�X�R���e�L�X�g�փZ�b�g
	GetDevContext()->OMSetBlendState(state, Math::Color(0,0,0,0), 0xFFFFFFFF);

	// ���(�����ł͎Q�ƃJ�E���^��-1����邾��)
	state->Release();
}

void KdDirect3D::DrawVertices(D3D_PRIMITIVE_TOPOLOGY topology,int vertexCount, const void* pVertexStream, UINT stride)
{
	
	// �v���~�e�B�u�g�|���W�[���Z�b�g
	GetDevContext()->IASetPrimitiveTopology(topology);

	// �S���_�̑��o�C�g�T�C�Y
	UINT totalSize = vertexCount * stride;


#if 1

	// ���_�o�b�t�@�̃T�C�Y���������Ƃ��́A���T�C�Y�̂��ߍč쐬����
	if (m_tempVertexBuffer.GetBufferSize() < totalSize) {
		m_tempVertexBuffer.Create(D3D11_BIND_VERTEX_BUFFER, totalSize, D3D11_USAGE_DYNAMIC, nullptr);
	}

	//============================================================
	//
	// �P����DISCARD�ł̏������݁B
	//  DISCARD�́A�V���ȃo�b�t�@������ō쐬���A�O��̃o�b�t�@�͎g���I���Ɩ����ɂ�����̂ł��B
	//  �܂菑�����ޓx�ɐV�K�̃o�b�t�@�ɂȂ銴���ł��B
	//  �o�b�t�@�̃T�C�Y���傫���ƁA���̕��V�K�̃o�b�t�@���쐬���鎞�Ԃ��������Ă��܂��܂��B
	//  ��������P�������ꍇ�́A�uDISCARD��NO_OVERWRITE�̑g�ݍ��킹�Z�v�̕��@�ōs���ق����悢�ł��B
	//
	//============================================================

	// �S���_���o�b�t�@�ɏ�������(DISCARD�w��)
	m_tempVertexBuffer.WriteData(pVertexStream, totalSize);

	// ���_�o�b�t�@�[���f�o�C�X�փZ�b�g
	{
		UINT offset = 0;
		D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_tempVertexBuffer.GetAddress(), &stride, &offset);
	}

	// �`��
	GetDevContext()->Draw(vertexCount, 0);

#else
	//============================================================
	//
	// DISCARD��NO_OVERWRITE�̑g�ݍ��킹�Z
	// https://msdn.microsoft.com/ja-jp/library/ee416245(v=vs.85).aspx
	//
	//  DISCARD�݂̂��Ə�L�̐����ŏ����Ă���悤�ɁA�o�b�t�@�T�C�Y���傫���Ȃ��
	//  ���x�ቺ���������Ȃ��Ă��܂��B
	//  ���̕��@���ƁA�o�b�t�@�̍č쐬�ł���DISCARD�̉񐔂����炷���Ƃ��o����̂ŁA
	//  ���x�ቺ���}�V�ɂ��邱�Ƃ��o���܂��B
	//
	//============================================================

	// ����̃o�b�t�@�쐬�B�傫�߂ɍ쐬���Ă����B
	if (m_tempVertexBuffer.GetBufferSize() == 0) {
		static const UINT kMaxBufferSize = 1000000;
		m_tempVertexBuffer.Create(D3D11_BIND_VERTEX_BUFFER, kMaxBufferSize, D3D11_USAGE_DYNAMIC, nullptr);
	}

	// ���݂̃o�b�t�@�������݈ʒu(byte)
	static UINT currentPos = 0;

	// ���݈ʒu����o�b�t�@�̃T�C�Y���I�[�o�[����ꍇ��DISCARD(�܂�V�K�Ńo�b�t�@��p�ӂ���)
	if (currentPos + totalSize >= m_tempVertexBuffer.GetBufferSize()) {

		// �o�b�t�@�͐V�K�ŗp�ӂ���Ă���̂ŁA�擪����o�b�t�@�ɏ�������
		char* p = (char*)m_tempVertexBuffer.Map(D3D11_MAP_WRITE_DISCARD);
		memcpy(p, pVertexStream, totalSize);
		m_tempVertexBuffer.Unmap();

		// ���_�o�b�t�@�[���f�o�C�X�փZ�b�g
		{
			UINT offset = 0;
			D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_tempVertexBuffer.GetAddress(), &stride, &offset);
		}

		// �`��
		GetDevContext()->Draw(vertexCount, 0);

		// ����̏������݈ʒu�ɐi�߂�
		currentPos = totalSize;
	}
	// �T�C�Y�I�[�o�[���Ȃ��ꍇ�́ANO_OVERWRITE�Ńo�b�t�@�̓r�����珑������
	else {
		// �o�b�t�@�̓r���ɏ������� ��currentPos�ȑO�̏ꏊ�́A���ݕ`��Ŏg�p����������Ȃ��̂Ő�΂ɐG���Ă̓_��
		char* p = (char*)m_tempVertexBuffer.Map(D3D11_MAP_WRITE_NO_OVERWRITE);
		memcpy(&p[currentPos], pVertexStream, totalSize);
		m_tempVertexBuffer.Unmap();

		// �������񂾈ʒu��擪�ɁA���_�o�b�t�@�[���f�o�C�X�փZ�b�g
		{
			D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_tempVertexBuffer.GetAddress(), &stride, &currentPos);
		}

		// �`��
		GetDevContext()->Draw(vertexCount, 0);

		// ���ɏ������ވʒu�ɐi�߂�
		currentPos += totalSize;
	}
#endif
	
}


