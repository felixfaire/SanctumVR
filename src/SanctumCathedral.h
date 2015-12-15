//
//  SanctumCathedral.h
//  SanctumVR
//
//  Created by Felix Faire on 15/12/2015.
//
//

#ifndef SanctumCathedral_h
#define SanctumCathedral_h

using namespace ci;
using namespace ci::app;
using namespace std;



class SanctumCathedral
{
public:
    SanctumCathedral()
    {
    }
    
    void setupModel()
    {
        gl::Texture::Format format;
        format.enableMipmapping( true );
        format.setMaxAnisotropy( 32.0f );
        
        gl::ShaderDef glsl = gl::ShaderDef().texture().color();
        
        ObjLoader           vault( loadAsset( "obj/ArchElement.obj" ) );
        mVaultPipingTex =   gl::Texture::create( loadImage( loadAsset( "textures/ElyCeiling.png" ) ), format );
        mVaultTex =         gl::Texture::create( loadImage( loadAsset( "textures/ElyCeilingBack.jpg" ) ), format );
        mVault =            gl::Batch::create( vault, gl::getStockShader( glsl ) );
        
        ObjLoader           side( loadAsset( "obj/WindowSide.obj" ) );
        mWindowSidesTex =   gl::Texture::create( loadImage( loadAsset( "textures/ArchSides.jpg" ) ), format );
        mWindowSides =      gl::Batch::create( side, gl::getStockShader( glsl ) );

        mMainWindowsTex =   gl::Texture::create( loadImage( loadAsset( "textures/ElyEndWindows.jpg" ) ), format );
        mMainWindows =      gl::Batch::create( geom::Plane().size( vec2( 27.15f, 37.31f ) )
                                                            .normal( vec3( 0.0f, 0.0f, -1.0f ) ),
                                               gl::getStockShader( glsl ) );
        
        mFloorTex =         gl::Texture::create( loadImage( loadAsset( "textures/ElyFloor.jpg" ) ), format );
        mFloor =            gl::Batch::create( geom::Plane().size( vec2( 27.15f, 60.96f ) )
                                                            .normal( vec3( 0.0f, -1.0f, 0.0f ) ),
                                               gl::getStockShader( glsl ) );
       
        mWindowMullionsTex =gl::Texture::create( loadImage( loadAsset( "textures/ElySideWindowsBack2.png" ) ), format );
        mWindowPanesTex =   gl::Texture::create( loadImage( loadAsset( "textures/ElySideWindowsBack.jpg" ) ), format );
        mCentreMullionsTex =gl::Texture::create( loadImage( loadAsset( "textures/ElySideWindowsCentre2.png" ) ), format );
        mCentrePanesTex =   gl::Texture::create( loadImage( loadAsset( "textures/ElySideWindowsCentre.jpg" ) ), format );
        mWindows =          gl::Batch::create( geom::Plane().size( vec2( 12.19f, 37.31f ) )
                                                            .normal( vec3( 1.0f, 0.0f, 0.0f ) ),
                                               gl::getStockShader( glsl ) );
        
        mEndColumnsTex =   gl::Texture::create( loadImage( loadAsset( "textures/ElyEndColumns.jpg" ) ), format );
        mEndColumns =      gl::Batch::create( geom::Plane().size( vec2( 4.0f, 30.02f ) )
                                                           .normal( vec3( 0.0f, 0.0f, -1.0f ) ),
                                              gl::getStockShader( glsl ) );
        
        mWallsTex =        gl::Texture::create( loadImage( loadAsset( "textures/ElySideWalls.png" ) ), format );
        mWalls =           gl::Batch::create( geom::Plane().size( vec2( 12.19f, 37.31f ) )
                                                           .normal( vec3( 1.0f, 0.0f, 0.0f ) ),
                                              gl::getStockShader( glsl ) );
        
        

        gl::VertBatchRef lightMesh = gl::VertBatch::create( GL_TRIANGLES );
        lightMesh->begin( GL_TRIANGLE_STRIP );
        lightMesh->texCoord( 1.0f, 1.0f );
        lightMesh->vertex( vec3( -13.5, 25.5, -6.9 ) );
        
        lightMesh->texCoord( 0.0f, 1.0f );
        lightMesh->vertex( vec3( -11.7, 2.2, -5.8 ) );
        
        lightMesh->texCoord( 1.0f, 0.0f );
        lightMesh->vertex( vec3( 9.7, -6.0, 6.7 ) );
        
        lightMesh->texCoord( 0.0f, 0.0f );
        lightMesh->vertex( vec3( -7.6, -6.0, -3.5 ) );
        lightMesh->end();
        
        mLightTex =        gl::Texture::create( loadImage( loadAsset( "textures/LightBeam.png" ) ), format );
        mLightMesh =       gl::VboMesh::create( *lightMesh.get() );
        mLight =           gl::Batch::create( mLightMesh, gl::getStockShader( glsl ) );
    
    }
    
    void draw()
    {
        gl::color( 1.0f, 1.0f, 1.0f, 1.0f );
        drawMainWindows();
        drawEndColumns();
        drawCeiling();
        drawSideWindows();
        drawFloor();
        drawWindowSides();
        drawWalls();
        gl::color( 1.0f, 1.0f, 1.0f, 0.1f );
        drawLightBeams();
    }
    
    void drawCeiling()
    {
        mVaultTex->bind();
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                gl::pushMatrices();
                gl::translate( vec3( 0.0f, 31.71f, 24.38f - (float)i * 12.19f ) );
                gl::rotate( (j > 0 ? -1.0f : 1.0f) * M_PI * 0.5f, 0.0f, 1.0f, 0.0f );
                
                mVault->draw();
                gl::popMatrices();
            }
        }
        
        mVaultPipingTex->bind();
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                gl::pushMatrices();
                gl::translate( vec3( 0.0f, 31.51f, 24.38f - (float)i * 12.19f ) );
                gl::rotate( (j > 0 ? -1.0f : 1.0f) * M_PI * 0.5f, 0.0f, 1.0f, 0.0f );
                
                mVault->draw();
                gl::popMatrices();
            }
        }
    }
    
    void drawMainWindows()
    {
        mMainWindowsTex->bind();
        for (int i = 0; i < 2; i++)
        {
            gl::pushMatrices();
            gl::rotate( M_PI * (float)i, vec3( 0.0f, 1.0f, 0.0f ) );
            gl::translate( vec3( 0.0f, 12.0f, 30.48f ) );
            mMainWindows->draw();
            gl::popMatrices();
        }
    }
    
    void drawSideWindows()
    {
        mWindowPanesTex->bind();
        for (int i = -2; i < 3; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i != 0 && j != 0)
                {
                    gl::pushMatrices();
                    gl::translate( vec3( (float)j * 14.99f, 12.0f, (float)i * 12.19f ) );
                    gl::rotate( (float)M_PI * 0.5, -1.0f, 0.0f, 0.0f );
                    mWindows->draw();
                    gl::popMatrices();
                }
            }
        }
        
        mWindowMullionsTex->bind();
        for (int i = -2; i < 3; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i != 0 && j != 0)
                {
                    gl::pushMatrices();
                    gl::translate( vec3( (float)j * 14.77f, 12.0f, (float)i * 12.19f ) );
                    gl::rotate( (float)M_PI * 0.5, -1.0f, 0.0f, 0.0f );
                    mWindows->draw();
                    gl::popMatrices();
                }
            }
        }
        
        mCentrePanesTex->bind();
        for (int i = -1 ; i < 2; i++)
        {
            if (i != 0)
            {
                gl::pushMatrices();
                gl::translate( vec3( (float)i * 14.99, 12.0f, -0.15f ) );
                gl::rotate( (float)M_PI * 0.5, -1.0f, 0.0f, 0.0f );
                mWindows->draw();
                gl::popMatrices();
            }
        }
        
        mCentreMullionsTex->bind();
        for (int i = -1 ; i < 2; i++)
        {
            if (i != 0)
            {
                gl::pushMatrices();
                gl::translate( vec3( (float)i * 14.77, 12.0f, -0.15f ) );
                gl::rotate( (float)M_PI * 0.5, -1.0f, 0.0f, 0.0f );
                mWindows->draw();
                gl::popMatrices();
            }
        }
    }
    
    void drawFloor()
    {
        mFloorTex->bind();
        gl::pushMatrices();
        gl::translate( vec3( 0.0f, -6.6f, 0.0f ) );
        mFloor->draw();
        gl::popMatrices();
    }
    
    void drawEndColumns()
    {
        gl::disableDepthWrite();
        mEndColumnsTex->bind();
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (j != 0 && i != 0)
                {
                    gl::pushMatrices();
                    gl::translate( vec3( (float)i * 11.6f, 8.46f, (float)j * 30.0f ) );
                    mEndColumns->draw();
                    gl::popMatrices();
                }
            }
        }
        gl::enableDepthWrite();
    }
    
    void drawWindowSides()
    {
        mWindowSidesTex->bind();
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                gl::pushMatrices();
                gl::translate( vec3( j > 0 ? -13.57f : 13.57f, 26.91f, 24.38 - (float)i * 12.19f ) );
                gl::rotate( (j > 0 ? 1.0f : -1.0f) * (float)M_PI * 0.5f, 0.0f, 1.0f, 0.0f );
                mWindowSides->draw();
                gl::popMatrices();
            }
        }
    }
    
    void drawWalls()
    {
        mWallsTex->bind();
        for (int i = -2; i < 3; i++){
            for (int j = -1; j < 2; j++)
            {
                if (j != 0)
                {
                    gl::pushMatrices();
                    gl::translate( vec3( (float)j * 13.57f, 12.0f, (float)i * 12.19f ) );
                    gl::rotate( (float)M_PI * 0.5, -1.0f, 0.0f, 0.0f );
                    mWalls->draw();
                    gl::popMatrices();
                }
            }
        }
    }
    
    void drawLightBeams()
    {
        mLightTex->bind();
        for (int i = 0; i < 4; i++)
        {
            gl::pushMatrices();
            gl::translate( vec3( -1.0f, 0.0f, 19.5f - 13.22f * (float)i ) );
            mLight->draw();
            gl::popMatrices();
        }
    }
    
    gl::BatchRef        mVault;
    gl::TextureRef      mVaultTex;
    gl::TextureRef      mVaultPipingTex;
    
    gl::BatchRef        mMainWindows;
    gl::TextureRef      mMainWindowsTex;
    
    gl::BatchRef        mFloor;
    gl::TextureRef      mFloorTex;
    
    gl::BatchRef        mWindows;
    gl::TextureRef      mWindowPanesTex;
    gl::TextureRef      mWindowMullionsTex;
    gl::TextureRef      mCentrePanesTex;
    gl::TextureRef      mCentreMullionsTex;
    
    gl::BatchRef        mEndColumns;
    gl::TextureRef      mEndColumnsTex;
    
    gl::BatchRef        mWindowSides;
    gl::TextureRef      mWindowSidesTex;
    
    gl::BatchRef        mWalls;
    gl::TextureRef      mWallsTex;
    
    gl::VboMeshRef      mLightMesh;
    gl::BatchRef        mLight;
    gl::TextureRef      mLightTex;
    
};

#endif /* SanctumCathedral_h */
