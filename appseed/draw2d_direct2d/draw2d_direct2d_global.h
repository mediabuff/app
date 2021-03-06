#pragma once


// Windows Desktop Thread Local Storage for Draw2d Direct2d plugin


interface IDWriteFactory;
interface ID2D1Factory1;
interface ID3D11Device;
interface ID3D11DeviceContext;
interface ID3D11Device1;
interface IDXGIDevice;


CLASS_DECL_DRAW2D_DIRECT2D ID2D1Factory1 * get_d2d1_factory1(bool bCreate = true);
CLASS_DECL_DRAW2D_DIRECT2D IDWriteFactory * global_draw_get_write_factory(bool bCreate = true);
CLASS_DECL_DRAW2D_DIRECT2D ID3D11Device * global_draw_get_d3d11_device();
CLASS_DECL_DRAW2D_DIRECT2D ID3D11Device1 * global_draw_get_d3d11_device1();
CLASS_DECL_DRAW2D_DIRECT2D ID3D11DeviceContext * global_draw_get_d3d11_device_context(); // Immediate Device Context
CLASS_DECL_DRAW2D_DIRECT2D ID3D11DeviceContext1 * global_draw_get_d3d11_device_context1(); // Immediate Device Context
CLASS_DECL_DRAW2D_DIRECT2D IDXGIDevice * global_draw_get_dxgi_device();
CLASS_DECL_DRAW2D_DIRECT2D ID2D1Device * global_draw_get_d2d1_device();



CLASS_DECL_DRAW2D_DIRECT2D float point_dpi(float points);
CLASS_DECL_DRAW2D_DIRECT2D float dpiy(float y);
CLASS_DECL_DRAW2D_DIRECT2D float dpix(float y);
CLASS_DECL_DRAW2D_DIRECT2D float y_dpi(float y);
CLASS_DECL_DRAW2D_DIRECT2D float x_dpi(float y);

