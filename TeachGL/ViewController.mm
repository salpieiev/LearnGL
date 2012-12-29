//
//  ViewController.m
//  TeachGL
//
//  Created by Sergey Alpeev on 26.12.12.
//  Copyright (c) 2012 Sergey Alpeev. All rights reserved.
//

#import "ViewController.h"
#include "Renderer.h"



@interface ViewController ()
{
    Renderer *m_renderer;
}

@property (strong, nonatomic) EAGLContext *context;

@end



@implementation ViewController

#pragma mark - Lifecykle

- (id)init
{
    self = [super init];
    if (self)
    {
        
    }
    return self;
}

- (void)dealloc
{
    delete m_renderer;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View Lifecykle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.preferredFramesPerSecond = 60;
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    [EAGLContext setCurrentContext:self.context];
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableMultisample = GLKViewDrawableMultisample4X;
    
    CGFloat width = CGRectGetWidth(self.view.frame);
    CGFloat height = CGRectGetHeight(self.view.frame);
    m_renderer = new Renderer((int)width, (int)height);
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    m_renderer->Render();
}

@end
