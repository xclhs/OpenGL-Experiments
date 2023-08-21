// This program draws a red square on a white background.

#include "Angel.h"

const int NumPoints = 6;

//----------------------------------------------------------------------------
//初始化函数

void
init( void )
{
    // Specifiy the vertices for two triangles
    //正方形被分割为两个三角形
    vec2 points[NumPoints] = {
        vec2( -0.5, -0.5 ), vec2( 0.5, -0.5 ), vec2( -0.5, 0.5 ),
        vec2( -0.5, 0.5 ), vec2( 0.5, -0.5 ), vec2( 0.5, 0.5 )
    };

    //GLuint即指定位数的unsigned int
    //无符号四字节整型
    GLuint vao;
    //分配一个顶点数组对象的名称
    glGenVertexArrays( 1, &vao );
    //创建一个顶点数组对象，并与其名称进行关联
    glBindVertexArray( vao );
    // Create and initialize a buffer object
    GLuint buffer;
    //生成缓冲区对象的名称
    glGenBuffers( 1, &buffer );
    //将缓冲对象进行绑定
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    //赋值
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    //创建顶点着色器和片元着色器
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                            (void*)0);

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )//展示函数
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    glDrawArrays( GL_TRIANGLES, 0, NumPoints );    // draw the triangles
    glFlush();
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    //初始化GLUT库，从main函数获取对应的两个参数
    glutInit( &argc, argv );
    //初始化窗口，指定其显示模式（GBA表示颜色模式）
    glutInitDisplayMode( GLUT_RGBA );
    //设置窗口大小
    glutInitWindowSize( 512, 512 );
    //设置所需的opengl的环境
    glutInitContextVersion( 3, 1 );
    //时候核心模式即不能兼容废弃功能
    glutInitContextProfile( GLUT_CORE_PROFILE );
    //创建窗口并对其命名
    glutCreateWindow( "SA21168286余婉莹" );

    if ( glewInit() != GLEW_OK )
    {
        std::cerr << "Failed to initialize GLEW ... exiting" << std::endl;
        exit( EXIT_FAILURE );
    }

    init();

    glutDisplayFunc( display );

    glutMainLoop();
}
