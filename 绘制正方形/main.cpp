// This program draws a red square on a white background.

#include "Angel.h"

const int NumPoints = 6;

//----------------------------------------------------------------------------
//��ʼ������

void
init( void )
{
    // Specifiy the vertices for two triangles
    //�����α��ָ�Ϊ����������
    vec2 points[NumPoints] = {
        vec2( -0.5, -0.5 ), vec2( 0.5, -0.5 ), vec2( -0.5, 0.5 ),
        vec2( -0.5, 0.5 ), vec2( 0.5, -0.5 ), vec2( 0.5, 0.5 )
    };

    //GLuint��ָ��λ����unsigned int
    //�޷������ֽ�����
    GLuint vao;
    //����һ������������������
    glGenVertexArrays( 1, &vao );
    //����һ������������󣬲��������ƽ��й���
    glBindVertexArray( vao );
    // Create and initialize a buffer object
    GLuint buffer;
    //���ɻ��������������
    glGenBuffers( 1, &buffer );
    //�����������а�
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    //��ֵ
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    //����������ɫ����ƬԪ��ɫ��
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
display( void )//չʾ����
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    glDrawArrays( GL_TRIANGLES, 0, NumPoints );    // draw the triangles
    glFlush();
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    //��ʼ��GLUT�⣬��main������ȡ��Ӧ����������
    glutInit( &argc, argv );
    //��ʼ�����ڣ�ָ������ʾģʽ��GBA��ʾ��ɫģʽ��
    glutInitDisplayMode( GLUT_RGBA );
    //���ô��ڴ�С
    glutInitWindowSize( 512, 512 );
    //���������opengl�Ļ���
    glutInitContextVersion( 3, 1 );
    //ʱ�����ģʽ�����ܼ��ݷ�������
    glutInitContextProfile( GLUT_CORE_PROFILE );
    //�������ڲ���������
    glutCreateWindow( "SA21168286����Ө" );

    if ( glewInit() != GLEW_OK )
    {
        std::cerr << "Failed to initialize GLEW ... exiting" << std::endl;
        exit( EXIT_FAILURE );
    }

    init();

    glutDisplayFunc( display );

    glutMainLoop();
}
