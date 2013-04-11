//
//  ViewController.m
//  TeachGL
//
//  Created by Sergey Alpeev on 26.12.12.
//  Copyright (c) 2012 Sergey Alpeev. All rights reserved.
//

#import "ViewController.h"
#include "Renderer.h"
#import <QuartzCore/QuartzCore.h>



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
    
    m_renderer = new Renderer();
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    CGFloat screenScale = [UIScreen mainScreen].scale;
    
    CGFloat width = screenScale * CGRectGetWidth(self.view.frame);
    CGFloat height = screenScale * CGRectGetHeight(self.view.frame);
    
    CFTimeInterval mediaTime = CACurrentMediaTime();
    
    m_renderer->Render((int)width, (int)height, mediaTime);
}

@end
